package View;

import View.Commands.Command;

import java.util.HashMap;
import java.util.Scanner;

public class TextMenu {
    private HashMap<String, Command> commands;
    public TextMenu() {
        commands = new HashMap<>();
    }
    public void addCommand(Command c) {
        commands.put(c.getKey(), c);
    }
    private void printMenu() {
        commands.keySet().stream()
                .sorted((key1, key2) -> Integer.compare(Integer.parseInt(key1), Integer.parseInt(key2)))
                .forEach(key -> {
                    Command com = commands.get(key);
                    String line = String.format(key + ": " + com.getDescription());
                    System.out.println(line);
                });
//        for (Command com : commands.values()) {
//            String line = String.format(com.getKey() + ": " + com.getDescription());
//            System.out.println(line);
//        }
    }
    public void show() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            printMenu();
            System.out.print("Input the option: ");
            String key = scanner.nextLine();
            Command com = commands.get(key);
            if (com == null) {
                System.out.println("Invalid option!");
                continue;
            }
            com.execute();
        }
    }
}
