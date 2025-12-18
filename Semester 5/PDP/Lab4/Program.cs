using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Lab4
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] urls = {
                "http://demo.borland.com/testsite/stadyn_largepagewithimages.html"
            };

            // 1. Callbacks
            Console.WriteLine("\n=== 1. Callbacks ===");
            var events = new ManualResetEvent[urls.Length];
            for (int i = 0; i < urls.Length; i++)
            {
                events[i] = new ManualResetEvent(false);
                new Sol1_CallbackDownloader(urls[i], i + 1, events[i]).Start();
            }
            WaitHandle.WaitAll(events);

            // 2. Tasks (ContinueWith)
            Console.WriteLine("\n=== 2. Tasks (ContinueWith) ===");
            var tasks = new List<Task>();
            for (int i = 0; i < urls.Length; i++)
            {
                tasks.Add(new Sol2_TaskDownloader(urls[i], i).Start());
            }
            Task.WaitAll(tasks.ToArray());

            // 3. Async / Await
            Console.WriteLine("\n=== 3. Async/Await ===");
            var asyncTasks = new List<Task>();
            for (int i = 0; i < urls.Length; i++)
            {
                asyncTasks.Add(new Sol3_AsyncAwaitDownloader(urls[i], i).StartAsync());
            }
            Task.WaitAll(asyncTasks.ToArray());

            Console.WriteLine("\nAll tests are done.");


            // Test with alot of con
            int numberOfConnections = 1000; 
            
            // Destined url
            string targetUrl = "http://demo.borland.com/testsite/stadyn_largepagewithimages.html";
            Console.WriteLine($"Trying to connect {numberOfConnections} simultaneously to: {targetUrl}");
            Console.WriteLine("Preparing...");

            // Generate the url list
            string[] urlss = new string[numberOfConnections];
            for (int i = 0; i < numberOfConnections; i++)
            {
                urlss[i] = targetUrl;
            }

            // List to hold the tasks
            List<Task> activeTasks = new List<Task>();

            // Start timer
            Stopwatch sw = Stopwatch.StartNew();
            Console.WriteLine("Launching requests...");
            
            for (int i = 0; i < urlss.Length; i++)
            {
                // Use one of the solutions
                var downloader = new Sol2_TaskDownloader(urlss[i], i);
                
                // Call the starter and collect the tasks
                Task t = downloader.Start();
                activeTasks.Add(t);
            }
            Console.WriteLine($"All the {numberOfConnections} req were sent to the server!");
            Console.WriteLine("Waiting for responses...\n");
            try
            {
                // We wait until all tasks are done
                Task.WaitAll(activeTasks.ToArray());
            }
            catch (AggregateException)
            {
                // Ignore here because we count them in the results section
            }
            sw.Stop();

            // Results
            int successful = 0;
            int failed = 0;

            foreach (var t in activeTasks)
            {
                if (t.Status == TaskStatus.RanToCompletion) successful++;
                else failed++;
            }

            Console.WriteLine("---------------------------------------------------------------------");
            Console.WriteLine("FINAL RESULTS:");
            Console.WriteLine($"Total time: {sw.ElapsedMilliseconds} ms");
            Console.WriteLine($"Successful: {successful}");
            Console.WriteLine($"Failed:  {failed}");
        }
    }
}