

namespace Lab01;

public class BankAccount
{
    private string Id { get; set; }
    private int Balance { get; set; }

    private readonly int InitialBalance;

    public Mutex _mutex { get; set; }

private List<Operation> Operations { get; set; }

    public BankAccount(int initialBalance, int accountId)
    {
        Id = accountId.ToString();//Guid.NewGuid().ToString();
        Operations = new List<Operation>();
        Balance = initialBalance;
        _mutex = new Mutex();
        InitialBalance = initialBalance;

    }

    public bool Transfer(int operationNumber, int amount, BankAccount account)
    {
        
        Mutex first, second;
        if (Int32.Parse(Id) < Int32.Parse(account.Id))
        {
            first = _mutex; 
            second = account._mutex; 
        }
        else
        {
            first = account._mutex;
            second = _mutex;
        }
        first.WaitOne();
        second.WaitOne();

        Operations.Add(new Operation(operationNumber, amount, account.Id, Id));
        Balance = Balance - amount;
        account.Operations.Add(new Operation(operationNumber, amount,  account.Id, Id ));
        account.Balance += amount;
        
        second.ReleaseMutex();
        first.ReleaseMutex();
        return true;
    }

    public bool ConsistencyCheck()
    {
        _mutex.WaitOne();
        int currentBalance = Balance;
        foreach (var operation in Operations)
        {
            if (operation.CreditorAccount == Id)
            {
                currentBalance += operation.Amount;
            }
            else
            {
                currentBalance -= operation.Amount;
            }
        }
        bool consistent = true;
        if (currentBalance != InitialBalance)
        {
            Console.WriteLine(Id.ToString());
            Console.WriteLine(currentBalance.ToString());
            Console.WriteLine(InitialBalance.ToString());
            consistent = false;
        }
        _mutex.ReleaseMutex();
        return consistent;
    }

    public override string ToString()
    {
        string operationsString = String.Join("\n           ", Operations);
        return $"{Id} - {Balance}:\n" +
               $"           {operationsString}";
    }
}