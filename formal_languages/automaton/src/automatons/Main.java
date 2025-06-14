package automatons;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String filePath = "src/automatons/resources/savenfa.txt";

        try {
            try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
                String line;

                while ((line = reader.readLine()) != null) {
                    line = line.trim();
                    if (line.startsWith("type:")) {
                        String type = line.split(":")[1].trim();
                        if (type.equals("dfa")) {
                            activateDFA(filePath);
                        }
                        else if (type.equals("nfa")) {
                            activateNFA(filePath);
                        }
                        else if (type.equals("enfa")) {
                            activateENFA(filePath);
                        }
                        break;
                    }
                }
            }

        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private static void activateDFA(String filePath) throws IOException {
        AutomatonDFA automaton = AutomatonDFA.readFromFile(filePath);
        System.out.println("""
                Available commands:
                1. accept - accept new word, use "accept: [word]"
                2. print - print table
                3. stop - exit program
                """);

        String command = command();
        while (!command.startsWith("stop")) {

            if (command.startsWith("accept")) {
                String word = command.split(":")[1].trim();
                boolean answer = automaton.accepts(word);
                if (answer) {
                    System.out.println("Accepted");
                }
                else {
                    System.out.println("Not accepted");
                }
            }
            else if (command.startsWith("print")) {
                automaton.printTable();
            }

            System.out.println("New command:");
            command = command();
        }
    }

    private static void activateNFA(String filePath) throws IOException {
        AutomatonNFA automaton = AutomatonNFA.readFromFile(filePath);
        System.out.println("""
                Available commands:
                1. accept - accept new word, use "accept: [word]"
                2. print - print table
                3. create - create DFA, use "create: 1" to show rename dictionary
                4. stop - exit program
                """);

        String command = command();
        while (!command.startsWith("stop")) {

            if (command.startsWith("accept")) {
                String word = command.split(":")[1].trim();
                boolean answer = automaton.accepts(word);
                if (answer) {
                    System.out.println("Accepted");
                }
                else {
                    System.out.println("Not accepted");
                }
            }
            else if (command.startsWith("print")) {
                automaton.printTable();
            }
            else if (command.startsWith("create")) {
                boolean params = command.split(":")[1].trim().equals("1");
                AutomatonDFA dfa = automaton.createDFA(params);
                dfa.printTable();
                System.out.println("Save new automaton? Y/N");
                command = command();
                if (command.equals("Y")) {
                    System.out.println("Input file name:");
                    String fileName = command();
                    dfa.saveToFile(fileName);
                }
            }

            System.out.println("New command:");
            command = command();
        }
    }

    private static void activateENFA(String filePath) throws IOException {
        AutomatonENFA automaton = AutomatonENFA.readFromFile(filePath);
        System.out.println("""
                Available commands:
                1. accept - accept new word, use "accept: [word]"
                2. print - print table
                3. create - create NFA
                4. stop - exit program
                """);

        String command = command();
        while (!command.startsWith("stop")) {

            if (command.startsWith("accept")) {
                String word = command.split(":")[1].trim();
                boolean answer = automaton.accepts(word);
                if (answer) {
                    System.out.println("Accepted");
                }
                else {
                    System.out.println("Not accepted");
                }
            }
            else if (command.startsWith("print")) {
                automaton.printTable();
            }
            else if (command.startsWith("create")) {
                AutomatonNFA nfa = automaton.createNFA();
                nfa.printTable();
                System.out.println("Save new automaton? Y/N");
                command = command();
                if (command.equals("Y")) {
                    System.out.println("Input file name:");
                    String fileName = command();
                    nfa.saveToFile(fileName);
                }
            }

            System.out.println("New command:");
            command = command();
        }
    }

    private static String command() {
        Scanner scanner = new Scanner(System.in);
        return scanner.nextLine();
    }
}