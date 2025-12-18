using System;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Lab4
{
    public class Sol3_AsyncAwaitDownloader
    {
        private Socket _socket;
        private readonly string _hostname;
        private readonly string _path;
        private readonly int _id;

        public Sol3_AsyncAwaitDownloader(string url, int id)
        {
            var uri = new Uri(url);
            _hostname = uri.Host;
            _path = uri.AbsolutePath == "" ? "/" : uri.AbsolutePath;
            _id = id;
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        public async Task StartAsync()
        {
            Console.WriteLine($"[Async {_id}] Connecting...");
            await _socket.ConnectAsync(HttpUtils.GetEndPoint(_hostname));

            var req = Encoding.ASCII.GetBytes(HttpUtils.BuildGetRequest(_hostname, _path));
            await _socket.SendAsync(req);

            byte[] buffer = new byte[1024];
            StringBuilder response = new StringBuilder();

            while (true)
            {
                int bytesRead = await _socket.ReceiveAsync(buffer);
                if (bytesRead == 0) break;

                response.Append(Encoding.ASCII.GetString(buffer, 0, bytesRead));

                string content = response.ToString();
                if (content.Contains("\r\n\r\n"))
                {
                    int headerEnd = content.IndexOf("\r\n\r\n");
                    int contentLength = HttpUtils.GetContentLength(content.Substring(0, headerEnd));
                    if ((content.Length - (headerEnd + 4)) >= contentLength)
                    {
                        Console.WriteLine($"[Async {_id}] Finished! Size: {contentLength}");
                        break;
                    }
                }
            }
            _socket.Close();
        }
    }
}