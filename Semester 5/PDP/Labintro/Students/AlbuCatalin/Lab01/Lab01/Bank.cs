namespace Lab01;

public class Bank
{
    private int _operationUniqueSerialNumber = 0;
    private List<BankAccount> accounts;
    private Mutex operation_number_mutex;
    private Mutex print_mutex;
    private int _checkIndex;
    private Random rnd = new Random();


    public Bank()
    {
        _checkIndex = 1;
        operation_number_mutex = new Mutex();
        print_mutex = new Mutex();
        accounts = new List<BankAccount>();
        for (int i = 0; i < 5; i++)
        {
            accounts.Add(new BankAccount(10000, i));
        }
    }

    private ValueTuple<int, int, int> GenerateRandomTransferData()
    {
        int randomTransferAccount1 = rnd.Next(5);
        int randomTransferAccount2  = rnd.Next(5);
        while (randomTransferAccount2 == randomTransferAccount1)
            randomTransferAccount2 = rnd.Next(5);
        int randomSum = rnd.Next(100);
        return new ValueTuple<int, int, int>(randomTransferAccount1, randomTransferAccount2, randomSum);
    }

   public void MakeTransactions()
   {
       List<Task> tasks = new List<Task>();
        for (int i = 0; i < 100; i++)
        {
        
            Task t = Task.Factory.StartNew(() =>
            {
                Console.WriteLine("Running transactions...");
                
                ValueTuple<int, int, int> transferData = GenerateRandomTransferData();
                operation_number_mutex.WaitOne();
                int opNum = _operationUniqueSerialNumber++;
                operation_number_mutex.ReleaseMutex();
                accounts[transferData.Item1].Transfer(opNum, transferData.Item3, accounts[transferData.Item2]);
            });
            tasks.Add(t);
            if (i % 10 == 9)
            {
                Task tc = Task.Factory.StartNew(() =>
                {
                    print_mutex.WaitOne();
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.WriteLine($"Consistency Check {_checkIndex}");
                    Console.ResetColor();
                    ConsistencyCheck();
                    _checkIndex++;
                    print_mutex.ReleaseMutex();
                });
                tasks.Add(tc);
            }
        }

        Task.WaitAll(tasks.ToArray());
        Console.ForegroundColor = ConsoleColor.Yellow;
        Console.WriteLine("Final Consistency Check");
        Console.ResetColor();
        ConsistencyCheck();
        Console.WriteLine(this.ToString());

   }

   private void ConsistencyCheck()
   {
       bool consistent = true;
       foreach (var bankAccount in accounts)
       {
           if(bankAccount.ConsistencyCheck() == false)
           {
               consistent = false;
               break;
           }
       }

       if (consistent)
       {
           Console.ForegroundColor = ConsoleColor.Green;
           Console.WriteLine("CONSISTENCY CHECK PASS");
           Console.ResetColor();
       }
       else
       {
           Console.ForegroundColor = ConsoleColor.Red;
           Console.WriteLine("CONSISTENCY CHECK FAIL");
           Console.ResetColor();
           Console.WriteLine(this.ToString());
       }
   }
   
    public override string ToString()
    {
        string res = "All accounts: \n";
        foreach (var bankAccount in accounts)
        {
            res += bankAccount.ToString() + "\n";
        }

        return res;
    }
}