namespace Lab01;

public class Operation
{
    public int UniqueSerialNumber { get; private set; }
    public int Amount { get; private set; }
    public string DebtorAccount { get; private set; }
    public string CreditorAccount { get; private set; }

    public Operation(int uniqueSerialNumber, int amount, string debtorAccount, string creditorAccount )
    {
        UniqueSerialNumber = uniqueSerialNumber;
        Amount = amount;
        DebtorAccount = debtorAccount;
        CreditorAccount = creditorAccount;
    }

    public override string ToString()
    {
        return $"{UniqueSerialNumber}: CA:{CreditorAccount} DA:{DebtorAccount} Amount:{Amount}";
    }
}