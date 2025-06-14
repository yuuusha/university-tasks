package automatons;

import java.io.*;
import java.util.*;

public class AutomatonDFA {
    private final AutomatonType automatonType;
    private final List<String> states;
    private final List<String> alphabet;
    private final String startState;
    private final Set<String> finalStates;
    private final Map<String, Map<String, String>> transitionTable;

    public AutomatonDFA(List<String> states, List<String> alphabet, String startState, Set<String> finalStates, Map<String, Map<String, String>> transitionTable, AutomatonType automatonType) {
        this.states = states;
        this.alphabet = alphabet;
        this.startState = startState;
        this.finalStates = finalStates;
        this.transitionTable = transitionTable;
        this.automatonType = automatonType;
    }

    public static AutomatonDFA readFromFile(String filePath) throws IOException {

        AutomatonType automatonType = null;
        String startState = null;
        List<String> states = new ArrayList<>();
        List<String> alphabet = new ArrayList<>();
        Set<String> finalStates = new HashSet<>();
        Map<String, Map<String, String>> transitionTable = new HashMap<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {

            String line;

            while ((line = reader.readLine()) != null) {

                line = line.trim();

                if (line.startsWith("type:")) {

                    String type = line.split(":")[1].trim();
                    automatonType = AutomatonType.fromString(type);

                } else if (line.startsWith("states:")) {

                    String[] statesArray = line.split(":")[1].trim().split(",\\s*");
                    states.addAll(Arrays.asList(statesArray));

                } else if (line.startsWith("alphabet:")) {

                    String[] alphabetArray = line.split(":")[1].trim().trim().split(",\\s*");
                    alphabet.addAll(Arrays.asList(alphabetArray));

                } else if (line.startsWith("start:")) {

                    startState = line.split(":")[1].trim().trim();

                } else if (line.startsWith("final:")) {

                    String[] finalStatesArray = line.split(":")[1].trim().trim().split(",\\s*");
                    finalStates.addAll(Arrays.asList(finalStatesArray));

                } else if (line.equals("table")) {

                    for (String state : states) {
                        line = reader.readLine();
                        String[] transitions = line.split(" ");
                        Map<String, String> temp = new HashMap<>();
                        int i = 0;
                        for (String symbol : alphabet) {
                            temp.put(symbol, transitions[i]);
                            i++;
                        }
                        transitionTable.put(state, new HashMap<>(temp));
                    }

                }
            }
        }
        return new AutomatonDFA(new ArrayList<>(states), new ArrayList<>(alphabet), startState, new HashSet<>(finalStates), new HashMap<>(transitionTable), automatonType);
    }

    public boolean accepts(String input) {
        String currentState = startState;

        for (char symbol : input.toCharArray()) {
            String symbolStr = String.valueOf(symbol);
            if (!alphabet.contains(symbolStr)) {
                throw new IllegalArgumentException("Input contains invalid symbol: " + symbolStr);
            }

            try {
                Map<String, String> transitions = transitionTable.get(currentState);

                System.out.print("Current state: " + currentState + ", current symbol: " + symbol + " -> ");
                currentState = transitions.get(symbolStr);

                if (currentState.equals("-")) {
                    System.out.println("[]");
                    return false;
                    //throw new RuntimeException("There is no transition for the symbol: " + symbolStr);
                }

                System.out.println(currentState);
            }
            catch (RuntimeException e) {
                throw new RuntimeException("Input cannot be processed: " + e.getMessage());
            }
        }

        return finalStates.contains(currentState);
    }

    public void printTable() {

        System.out.println("Type: " + automatonType);

        int columnWidth = states.stream().map(String::length).max(Comparator.naturalOrder()).orElse(5) + 4;

        System.out.printf("%" + columnWidth + "s|", "");
        for (String symbol : alphabet) {
            System.out.printf("%" + columnWidth + "s|", symbol);
        }
        System.out.println();

        for (String state : states) {
            String stateMarker = (state.equals(startState) ? "-> " : "  ") + (finalStates.contains(state) ? "*" : " ") + state;

            System.out.printf("%" + columnWidth + "s|", stateMarker);

            for (String symbol : alphabet) {
                String nextState = transitionTable.get(state).get(symbol);
                System.out.printf("%" + columnWidth + "s|", nextState);
            }
            System.out.println();
        }
    }

    public void saveToFile(String filePath) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            writer.write("type: " + automatonType.toString().toLowerCase());
            writer.newLine();

            writer.write("states: " + String.join(", ", states));
            writer.newLine();

            writer.write("alphabet: " + String.join(", ", alphabet));
            writer.newLine();

            writer.write("start: " + startState);
            writer.newLine();

            writer.write("final: " + String.join(", ", finalStates));
            writer.newLine();

            writer.newLine();
            writer.write("table");
            writer.newLine();
            for (String state : states) {
                StringBuilder row = new StringBuilder();
                for (String symbol : alphabet) {
                    String nextState = transitionTable.getOrDefault(state, Map.of()).get(symbol);
                    row.append(nextState != null ? nextState : "-").append(" ");
                }
                writer.write(row.toString().trim());
                writer.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
