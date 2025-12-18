using System;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace Lab4
{
    public static class SocketExtensions
    {
        public static Task ConnectAsync(this Socket socket, EndPoint endPoint)
        {
            var tcs = new TaskCompletionSource<bool>();
            socket.BeginConnect(endPoint, ar =>
            {
                try 
                { 
                    socket.EndConnect(ar); 
                    tcs.TrySetResult(true); 
                }
                catch (Exception ex) { tcs.TrySetException(ex); }
            }, null);
            return tcs.Task;
        }

        public static Task<int> SendAsync(this Socket socket, byte[] buffer)
        {
            var tcs = new TaskCompletionSource<int>();
            socket.BeginSend(buffer, 0, buffer.Length, SocketFlags.None, ar =>
            {
                try 
                { 
                    int bytesSent = socket.EndSend(ar);
                    tcs.TrySetResult(bytesSent); 
                }
                catch (Exception ex) { tcs.TrySetException(ex); }
            }, null);
            return tcs.Task;
        }

        public static Task<int> ReceiveAsync(this Socket socket, byte[] buffer)
        {
            var tcs = new TaskCompletionSource<int>();
            socket.BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, ar =>
            {
                try 
                { 
                    int bytesRead = socket.EndReceive(ar);
                    tcs.TrySetResult(bytesRead); 
                }
                catch (Exception ex) { tcs.TrySetException(ex); }
            }, null);
            return tcs.Task;
        }
    }
}   