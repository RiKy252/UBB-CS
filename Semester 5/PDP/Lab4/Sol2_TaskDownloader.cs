using System;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Lab4
{
    public class Sol2_TaskDownloader
    {
        private Socket _socket;
        private readonly string _hostname;
        private readonly string _path;
        private readonly int _id;
        private byte[] _buffer = new byte[1024];
        private StringBuilder _response = new StringBuilder();

        public Sol2_TaskDownloader(string url, int id)
        {
            var uri = new Uri(url);
            _hostname = uri.Host;
            _path = uri.AbsolutePath == "" ? "/" : uri.AbsolutePath;
            _id = id;
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        public Task Start()
        {
            Console.WriteLine($"[Task {_id}] Connecting...");
            
            // Tasks chain
            return _socket.ConnectAsync(HttpUtils.GetEndPoint(_hostname))
                .ContinueWith(t => 
                {
                    var req = Encoding.ASCII.GetBytes(HttpUtils.BuildGetRequest(_hostname, _path));
                    return _socket.SendAsync(req);
                }).Unwrap()
                .ContinueWith(t => 
                {
                    // Prepare to receive data
                    return ReceiveLoop();
                }).Unwrap();
        }

        private Task ReceiveLoop()
        {
            return _socket.ReceiveAsync(_buffer).ContinueWith(t =>
            {
                int bytesRead = t.Result;
                if (bytesRead > 0)
                {
                    _response.Append(Encoding.ASCII.GetString(_buffer, 0, bytesRead));
                    if (CheckIfDone())
                    {
                        Console.WriteLine($"[Task {_id}] Finished!");
                        _socket.Close();
                        return Task.CompletedTask;
                    }
                    // Recursive to simulate a loop
                    return ReceiveLoop();
                }
                _socket.Close();
                return Task.CompletedTask;
            }).Unwrap();
        }

        private bool CheckIfDone()
        {
            string content = _response.ToString();
            if (content.Contains("\r\n\r\n"))
            {
                int headerEnd = content.IndexOf("\r\n\r\n");
                int contentLength = HttpUtils.GetContentLength(content.Substring(0, headerEnd));
                return (content.Length - (headerEnd + 4)) >= contentLength;
            }
            return false;
        }
    }
}