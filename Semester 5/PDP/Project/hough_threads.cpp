#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <sstream>

using namespace std;

const int THRESHOLD_VOTE = 300;
const double PI = 3.14159265358979323846;

struct Image {
    int width, height;
    vector<int> data; // pixel data
};

Image readPGM(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Cannot open " << filename << endl;
        exit(1);
    }

    string line, format;
    int w = 0, h = 0, maxVal = 0;

    // Parse Header
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        stringstream ss(line);
        if (format.empty()) ss >> format;
        if (w == 0 || h == 0) {
            if (!ss.eof()) ss >> w;
            if (!ss.eof()) ss >> h;
        }
        if (maxVal == 0 && w > 0 && h > 0 && !ss.eof()) ss >> maxVal;
        if (!format.empty() && w > 0 && h > 0 && maxVal > 0) break;
    }

    Image img;
    img.width = w;
    img.height = h;
    img.data.resize(w * h);

    if (format == "P2") {
        // ASCII
        for (int i = 0; i < w * h; i++) file >> img.data[i];
    } else if (format == "P5") {
        // Binary
        vector<unsigned char> buffer(w * h);
        file.read(reinterpret_cast<char*>(buffer.data()), w * h);
        for (int i = 0; i < w * h; i++) img.data[i] = static_cast<int>(buffer[i]);
    }
    return img;
}

void writePGM(const string& filename, const Image& img) {
    ofstream file(filename);
    file << "P2\n" << img.width << " " << img.height << "\n255\n";
    for (int i = 0; i < img.width * img.height; i++) {
        file << img.data[i] << " ";
        if ((i + 1) % img.width == 0) file << "\n";
    }
}

// Sobel Thread Worker
void sobelWorker(const Image& input, Image& output, int startRow, int endRow) {
    int w = input.width;
    int h = input.height;

    // Sobel Kernels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int y = startRow; y < endRow; y++) {
        // Safety check for image boundaries
        if (y == 0 || y == h - 1) continue;

        for (int x = 1; x < w - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            // Convolution 3x3
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int val = input.data[(y + i) * w + (x + j)];
                    sumX += val * Gx[i + 1][j + 1];
                    sumY += val * Gy[i + 1][j + 1];
                }
            }

            int magnitude = sqrt(sumX * sumX + sumY * sumY);
            
            // Convert to binary, if magnitude is met
            output.data[y * w + x] = (magnitude > 50) ? 255 : 0;
        }
    }
}

// Hough Voting Thread Worker
// Maps edge points (x,y) to parameter space (rho, theta)
void houghWorker(const Image& edges, vector<int>& localAcc, int accWidth, int accHeight, int startRow, int endRow, double rhoRes, double thetaRes) {
    int w = edges.width;
    int maxRho = sqrt(w * w + edges.height * edges.height);

    for (int y = startRow; y < endRow; y++) {
        for (int x = 0; x < w; x++) {
            // If pixel is an edge (white)
            if (edges.data[y * w + x] > 0) {
                // Vote for all possible angles
                for (int t = 0; t < accWidth; t++) {
                    double theta = t * thetaRes - PI / 2.0;
                    double rho = x * cos(theta) + y * sin(theta);
                    
                    // Normalize rho to array index
                    int rIdx = (int)(rho + maxRho) / rhoRes;
                    
                    if (rIdx >= 0 && rIdx < accHeight) {
                        localAcc[rIdx * accWidth + t]++;
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <num_threads> <input_filename>" << endl;
        return 1;
    }
    int numThreads = atoi(argv[1]); 
    string inputFile = argv[2];

    if (numThreads <= 0) {
        cerr << "Error: Number of threads must be > 0." << endl;
        return 1;
    }

    Image img = readPGM(inputFile);
    
    // Start Timer
    auto startTime = chrono::high_resolution_clock::now();

    // Sobel Phase
    Image edges;
    edges.width = img.width;
    edges.height = img.height;
    edges.data.resize(img.width * img.height, 0);

    vector<thread> threads;
    int rowsPerThread = img.height / numThreads;

    // Launch Sobel Threads
    for (int i = 0; i < numThreads; i++) {
        int startRow = i * rowsPerThread;
        if (startRow == 0) startRow = 1; 
        int endRow = (i == numThreads - 1) ? img.height - 1 : (i + 1) * rowsPerThread;
        
        threads.emplace_back(sobelWorker, ref(img), ref(edges), startRow, endRow);
    }
    for (auto& t : threads) t.join();
    threads.clear();
    
    // Write intermediate result (Proof of Edge Detection)
    writePGM("edges.pgm", edges);

    // 2. Hough Phase (Voting)
    double thetaRes = PI / 180.0;
    double rhoRes = 1.0;
    double maxRho = sqrt(img.width * img.width + img.height * img.height);
    int accWidth = 180;
    int accHeight = (int)(2 * maxRho / rhoRes) + 1;
    
    // Global Accumulator (Final Result)
    vector<int> globalAccumulator(accWidth * accHeight, 0);
    // Local Accumulators (Data Privatization to avoid Mutex)edges
    vector<vector<int>> localAccumulators(numThreads, vector<int>(accWidth * accHeight, 0));

    // Launch Hough Threads
    for (int i = 0; i < numThreads; i++) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? img.height : (i + 1) * rowsPerThread;

        threads.emplace_back(houghWorker, ref(edges), ref(localAccumulators[i]), accWidth, accHeight, startRow, endRow, rhoRes, thetaRes);
    }
    for (auto& t : threads) t.join();

    // Reduction Step: Merge local accumulators into global
    for (int i = 0; i < numThreads; i++) {
        for (int j = 0; j < accWidth * accHeight; j++) {
            globalAccumulator[j] += localAccumulators[i][j];
        }
    }

    // Stop Timer
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    // 3. Analyze Results
    int maxVotes = 0;
    for (int val : globalAccumulator) {
        if (val > maxVotes) maxVotes = val;
    }

    int linesFound = 0;
    // Simple logic: if a cell has enough votes, it's a line
    int effectiveThreshold = (maxVotes > THRESHOLD_VOTE) ? THRESHOLD_VOTE : (maxVotes / 2);    

    for (int i = 0; i < accWidth * accHeight; i++) {
        if (globalAccumulator[i] > effectiveThreshold) linesFound++;
    }

    // 4. Final Output
    cout << "\n========================================\n";
    cout << "   PARALLEL HOUGH TRANSFORM RESULTS\n";
    cout << "========================================\n";
    cout << "Input Image:    " << img.width << " x " << img.height << " pixels\n";
    cout << "Execution Mode: " << numThreads << " Threads\n";
    cout << "----------------------------------------\n";
    cout << "Peak Vote:      " << maxVotes << "\n";
    cout << "Threshold:      " << effectiveThreshold << "\n";
    cout << "Lines Detected: " << linesFound << "\n";
    cout << "----------------------------------------\n";
    cout << "Total Time:     " << elapsed.count() << " sec\n";
    cout << "========================================\n\n";

    return 0;
}