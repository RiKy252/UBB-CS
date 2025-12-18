using System;
using System.Net;

namespace Lab4
{
    public static class HttpUtils
    {
        // Extract Content-Length from HTTP header
        public static int GetContentLength(string responseHeaders)
        {
            var lines = responseHeaders.Split('\n');
            foreach (var line in lines)
            {
                var cleanLine = line.Trim();
                if (cleanLine.StartsWith("Content-Length:", StringComparison.OrdinalIgnoreCase))
                {
                    var parts = cleanLine.Split(':');
                    if (parts.Length > 1 && int.TryParse(parts[1].Trim(), out int length))
                    {
                        return length;
                    }
                }
            }
            return 0;
        }

        // Return IP
        public static IPEndPoint GetEndPoint(string hostname, int port = 80)
        {
            var hostEntry = Dns.GetHostEntry(hostname);
            return new IPEndPoint(hostEntry.AddressList[0], port);
        }

        // Return the get request as a string
        public static string BuildGetRequest(string hostname, string path)
        {
            return $"GET {path} HTTP/1.1\r\nHost: {hostname}\r\nConnection: close\r\n\r\n";
        }
    }
}