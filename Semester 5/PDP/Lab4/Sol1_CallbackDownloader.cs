using System;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace Lab4
{
    public class Sol1_CallbackDownloader
    {
        private Socket _socket;
        private readonly string _hostname;
        private readonly string _path;
        private readonly int _id;
        private readonly ManualResetEvent _doneEvent;

        private byte[] _buffer = new byte[1024];
        private StringBuilder _response = new StringBuilder();

        public Sol1_CallbackDownloader(string url, int id, ManualResetEvent doneEvent)
        {
            var uri = new Uri(url);
            _hostname = uri.Host;
            _path = uri.AbsolutePath == "" ? "/" : uri.AbsolutePath;
            _id = id;
            _doneEvent = doneEvent;
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        public void Start()
        {
            Console.WriteLine($"[Callback {_id}] Connecting...");
            _socket.BeginConnect(HttpUtils.GetEndPoint(_hostname), OnConnect, null);
        }

        private void OnConnect(IAsyncResult ar)
        {
            _socket.EndConnect(ar);
            var req = Encoding.ASCII.GetBytes(HttpUtils.BuildGetRequest(_hostname, _path));
            _socket.BeginSend(req, 0, req.Length, SocketFlags.None, OnSend, null);
        }

        private void OnSend(IAsyncResult ar)
        {
            _socket.EndSend(ar);
            _socket.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, OnReceive, null);
        }

        private void OnReceive(IAsyncResult ar)
        {
            int bytesRead = _socket.EndReceive(ar);
            if (bytesRead > 0)
            {
                _response.Append(Encoding.ASCII.GetString(_buffer, 0, bytesRead));
                if (CheckIfDone())
                {
                    Console.WriteLine($"[Callback {_id}] Finished!");
                    _socket.Close();
                    _doneEvent.Set(); // flag for main
                }
                else
                {
                    // Read one more time
                    _socket.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, OnReceive, null);
                }
            }
            else
            {
                _socket.Close();
                _doneEvent.Set();
            }
        }

        private bool CheckIfDone()
        {
            string content = _response.ToString();
            if (content.Contains("\r\n\r\n"))
            {
                int headerEnd = content.IndexOf("\r\n\r\n");
                int contentLength = HttpUtils.GetContentLength(content.Substring(0, headerEnd));
                int bodyLength = content.Length - (headerEnd + 4);
                return bodyLength >= contentLength;
            }
            return false;
        }
    }
}