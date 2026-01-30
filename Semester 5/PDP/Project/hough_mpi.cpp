#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <mpi.h> 

using namespace std;

const int THRESHOLD_VOTE = 60;
const double PI = 3.14159265358979323846;

struct Image {
    int width, height;
    vector<int> data;
};

void writePGM(const string& filename, const Image& img) {
    ofstream file(filename);
    file << "P2\n" << img.width << " " << img.height << "\n255\n";
    for (int i = 0; i < img.width * img.height; i++) {
        file << img.data[i] << " ";
        if ((i + 1) % img.width == 0) file << "\n";
    }
}

Image readPGM(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Cannot open " << filename << endl;
        exit(1);
    }

    string line, format;
    int w = 0, h = 0, maxVal = 0;

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
        for (int i = 0; i < w * h; i++) file >> img.data[i];
    } else if (format == "P5") {
        vector<unsigned char> buffer(w * h);
        file.read(reinterpret_cast<char*>(buffer.data()), w * h);
        for (int i = 0; i < w * h; i++) img.data[i] = static_cast<int>(buffer[i]);
    }
    return img;
}

void sobelRange(const Image& input, vector<int>& localEdges, int startRow, int endRow) {
    int w = input.width;
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int y = startRow; y < endRow; y++) {
        if (y == 0 || y == input.height - 1) continue;

        for (int x = 1; x < w - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int val = input.data[(y + i) * w + (x + j)];
                    sumX += val * Gx[i + 1][j + 1];
                    sumY += val * Gy[i + 1][j + 1];
                }
            }
            int magnitude = sqrt(sumX * sumX + sumY * sumY);
            localEdges[y * w + x] = (magnitude > 50) ? 255 : 0;
        }
    }
}

void houghRange(const vector<int>& edges, int width, vector<int>& localAcc, 
                int accWidth, int accHeight, int startRow, int endRow, 
                double rhoRes, double thetaRes, double maxRho) {
    
    for (int y = startRow; y < endRow; y++) {
        for (int x = 0; x < width; x++) {
            if (edges[y * width + x] > 0) {
                for (int t = 0; t < accWidth; t++) {
                    double theta = t * thetaRes - PI / 2.0;
                    double rho = x * cos(theta) + y * sin(theta);
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
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    Image img;
    int dims[2]; 

    if (world_rank == 0) {
        img = readPGM("input2.pgm");
        dims[0] = img.width;
        dims[1] = img.height;
        cout << "[MPI] Master: Imagine citita " << dims[0] << "x" << dims[1] << endl;
    }

    MPI_Bcast(dims, 2, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank != 0) {
        img.width = dims[0];
        img.height = dims[1];
        img.data.resize(img.width * img.height);
    }

    MPI_Bcast(img.data.data(), img.width * img.height, MPI_INT, 0, MPI_COMM_WORLD);

    int rowsPerRank = img.height / world_size;
    int startRow = world_rank * rowsPerRank;
    int endRow = (world_rank == world_size - 1) ? img.height : (world_rank + 1) * rowsPerRank;

    double startTime = MPI_Wtime();

    vector<int> localEdges(img.width * img.height, 0);
    sobelRange(img, localEdges, startRow, endRow);

    vector<int> globalEdges;
    if (world_rank == 0) {
        globalEdges.resize(img.width * img.height);
    }

    MPI_Reduce(localEdges.data(), 
               globalEdges.data(), 
               img.width * img.height, 
               MPI_INT, 
               MPI_SUM, 
               0, 
               MPI_COMM_WORLD);

    double thetaRes = PI / 180.0;
    double rhoRes = 1.0;
    double maxRho = sqrt(img.width * img.width + img.height * img.height);
    int accWidth = 180;
    int accHeight = (int)(2 * maxRho / rhoRes) + 1;

    vector<int> localAccumulator(accWidth * accHeight, 0);
    houghRange(localEdges, img.width, localAccumulator, accWidth, accHeight, startRow, endRow, rhoRes, thetaRes, maxRho);

    vector<int> globalAccumulator;
    if (world_rank == 0) {
        globalAccumulator.resize(accWidth * accHeight, 0);
    }

    MPI_Reduce(localAccumulator.data(), 
               globalAccumulator.data(), 
               accWidth * accHeight, 
               MPI_INT, 
               MPI_SUM, 
               0, 
               MPI_COMM_WORLD);

    double endTime = MPI_Wtime();

    if (world_rank == 0) {
        cout << "[MPI] Timp executie: " << (endTime - startTime) << " secunde." << endl;

        Image outImg;
        outImg.width = img.width;
        outImg.height = img.height;
        outImg.data = globalEdges;
        writePGM("edges2.pgm", outImg);
        cout << "[MPI] Imagine salvata in edges.pgm" << endl;

        int maxVotes = 0;
        for (int val : globalAccumulator) {
            if (val > maxVotes) maxVotes = val;
        }
        cout << "[MPI] Max voturi: " << maxVotes << endl;

        int effectiveThreshold = (maxVotes > THRESHOLD_VOTE) ? THRESHOLD_VOTE : (maxVotes / 2);
        int linesFound = 0;

        for (int i = 0; i < accWidth * accHeight; i++) {
            if (globalAccumulator[i] > effectiveThreshold) {
                linesFound++;
            }
        }
        cout << "[MPI] Linii detectate: " << linesFound << endl;
    }

    MPI_Finalize();
    return 0;
}