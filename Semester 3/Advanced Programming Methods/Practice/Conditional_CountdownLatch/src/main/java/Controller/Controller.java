package Controller;

import Model.ADTs.*;
import Model.PrgState;
import Model.Statements.IStmt;
import Model.Values.Value;
import MyException.*;
import Repository.IRepo;

import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private IRepo repository;
    private ExecutorService executor;
    private boolean displayFlag;
    int counter = 1;
    public Controller(IRepo repo) {
        this.repository = repo;
    }
    public void oneStepForAllPrg(List<PrgState> prgList) throws InterruptedException {
        // prgList.forEach(prg -> repository.logPrgStateExec(prg));
        List<Callable<PrgState>> callList = prgList.stream()
                .map((PrgState p) -> (Callable<PrgState>)() -> {return p.oneStepExec();})
                .collect(Collectors.toList());
        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (Exception e) {
                        System.out.println(e.getMessage());
                        return null;
                    }
                })
                .filter(p -> p != null)
                .collect(Collectors.toList());
        prgList.addAll(newPrgList);
        prgList.forEach(prg -> repository.logPrgStateExec(prg));
        repository.setPrgList(prgList);
    }
    public void allSteps() throws InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        List<PrgState> prgList = removeCompletedPrg(repository.getPrgList());
        while (prgList.size() > 0) {
            prgList.forEach(prg -> {
                IHeap<Integer, Value> heap = prg.getHeap();
                heap.setHeap(heap.safeGarbageCollector(prg.getReachableAddresses(), heap.getHeap()));
            });
            oneStepForAllPrg(prgList);
            prgList = removeCompletedPrg(repository.getPrgList());
        }
        executor.shutdownNow();
        repository.setPrgList(prgList);
    }
    public void displayCurrentState(PrgState program) {
        System.out.println(program.toString());
    }
    public List<PrgState> getPrograms() {
        return this.repository.getPrgList();
    }
    public void setDisplayFlag(boolean flag) {
        this.displayFlag = flag;
    }
    public List<PrgState> removeCompletedPrg(List<PrgState> inputPrgList) {
        return inputPrgList.stream()
                .filter(p -> p.isNotCompleted())
                .collect(Collectors.toList());
    }
    public List<IStmt> allExamples() {
        return repository.allExamples();
    }
    public void setProgram(IStmt program) {
        program.typeCheck(new MyDictionary<>());
        repository.clear();
        repository.addPrg(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(), new LatchTable(), program));
    }
    public void oneStep() throws InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        List<PrgState> prgList = removeCompletedPrg(repository.getPrgList());
        if (prgList.size() > 0) {
            prgList.forEach(prg -> {
                IHeap<Integer, Value> heap = prg.getHeap();
                heap.setHeap(heap.safeGarbageCollector(prg.getReachableAddresses(), heap.getHeap()));
            });
            oneStepForAllPrg(prgList);
            prgList = removeCompletedPrg(repository.getPrgList());
        }
        executor.shutdownNow();
        repository.setPrgList(prgList);
    }
}
