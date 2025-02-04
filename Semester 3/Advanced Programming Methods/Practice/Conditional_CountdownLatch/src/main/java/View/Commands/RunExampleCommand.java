package View.Commands;

import Controller.Controller;
import MyException.MyException;

public class RunExampleCommand extends Command {
    private Controller controller;
    public RunExampleCommand(String key, String desc, Controller c) {
        super(key, desc);
        this.controller = c;
    }
    @Override
    public void execute() {
        try {
            controller.allSteps();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
