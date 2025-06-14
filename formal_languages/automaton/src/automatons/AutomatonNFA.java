package automatons;

import java.io.*;
import java.util.*;

public class AutomatonNFA {
    private final AutomatonType automatonType;
    private final List<String> states;
    private final List<String> alphabet;
    private final String startState;
    private final Set<String> finalStates;
    private final Map<String, Map<String, String[]>> transitionTable;

    public AutomatonNFA(List<String> states, List<String> alphabet, String startState, Set<String> finalStates, Map<String, Map<String, String[]>> transitionTable, AutomatonType automatonType) {
        this.states = states;
        this.alphabet = alphabet;
        this.startState = startState;
        this.finalStates = finalStates;
        this.transitionTable = transitionTable;
        this.automatonType = automatonType;
    }

    public static AutomatonNFA readFromFile(String filePath) throws IOException {

        AutomatonType automatonType = null;
        String startState = null;
        List<String> states = new ArrayList<>();
        List<String> alphabet = new ArrayList<>();
        Set<String> finalStates = new HashSet<>();
        Map<String, Map<String, String[]>> transitionTable = new HashMap<>();

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
                        Map<String, String[]> temp = new HashMap<>();
                        int i = 0;
                        for (String symbol : alphabet) {
                            String[] doublesStates = transitions[i].split(",");
                            temp.put(symbol, doublesStates);
                            i++;
                        }
                        transitionTable.put(state, new HashMap<>(temp));
                    }

                }
            }
        }
        return new AutomatonNFA(new ArrayList<>(states), new ArrayList<>(alphabet), startState, new HashSet<>(finalStates), new HashMap<>(transitionTable), automatonType);
    }

    public boolean accepts(String input) {

        HashSet<String> currentStates = new HashSet<>();
        currentStates.add(startState);

        for (char symbol : input.toCharArray()) {
            String symbolStr = String.valueOf(symbol);
            if (!alphabet.contains(symbolStr)) {
                throw new IllegalArgumentException("Input contains invalid symbol: " + symbolStr);
            }

            try {
                System.out.print("Current states: " + currentStates.toString() + ", current symbol: " + symbol + " -> ");
                HashSet<String> tempCurrentStates = new HashSet<>();

                for (String state : currentStates) {
                    Map<String, String[]> transitions = transitionTable.get(state);

                    String[] newStates = transitions.get(symbolStr);
                    tempCurrentStates.addAll(Set.of(newStates));
                }
                currentStates.clear();
                currentStates.addAll(tempCurrentStates);

                if (currentStates.contains("-")) {
                    currentStates.remove("-");
                    //throw new RuntimeException("There is no transition for the symbol: " + symbolStr);
                }

                System.out.println(currentStates.toString());
            }
            catch (RuntimeException e) {
                throw new RuntimeException("Input cannot be processed: " + e.getMessage());
            }
        }

        for (String state : currentStates) {
            if (finalStates.contains(state)) {
                return true;
            }
        }
        return false;
    }

    public void printTable() {

        System.out.println("Type: " + automatonType);

        int columnWidth = transitionTable.values().stream()
                .flatMap(map -> map.values().stream())
                .mapToInt(arr -> arr.length * 3 - 2)
                .max()
                .orElse(5) + 2;

        System.out.printf("%" + 5 + "s|", "");
        for (String symbol : alphabet) {
            System.out.printf("%" + columnWidth + "s|", symbol);
        }
        System.out.println();

        for (String state : states) {
            String stateMarker = (state.equals(startState) ? "-> " : "  ") + (finalStates.contains(state) ? "*" : " ") + state;

            System.out.printf("%" + 5 + "s|", stateMarker);

            for (String symbol : alphabet) {
                String[] nextStates = transitionTable.get(state).get(symbol);
                System.out.printf("%" + columnWidth + "s|", collectionToString(nextStates));
            }
            System.out.println();
        }
    }

    private String collectionToString(String[] collection) {
        StringBuilder resString = new StringBuilder();
        for (String obj : collection) {
            if (!resString.isEmpty()) {
                resString.append(",");
            }
            resString.append(obj);
        }
        return resString.toString();
    }

    public AutomatonDFA createDFA(boolean showDictionary) {

        Set<String> currentStates = new HashSet<>();
        currentStates.add(startState);

        ArrayList<Set<String>> allStates = new ArrayList<>();
        allStates.add(currentStates);

        Map<String, Map<String, Set<String>>> tableAutomaton = new HashMap<>();
        Set<String> newFinalStates = new HashSet<>();

        while (!allStates.isEmpty()) {
            currentStates = allStates.removeFirst();

            Map<String, Set<String>> temp = new HashMap<>();
            for (String symbol : alphabet) {

                Set<String> stateForSymbol = new HashSet<>();
                for (String state : currentStates) {
                    String[] newStates = transitionTable.get(state).get(symbol);
                    stateForSymbol.addAll(Set.of(newStates));
                }

                stateForSymbol.remove("-");

                if (!tableAutomaton.containsKey(stateForSymbol.toString()) && !stateForSymbol.isEmpty()) {
                    allStates.add(stateForSymbol);
                }

                Set<String> intersection = new HashSet<>(finalStates);
                intersection.retainAll(stateForSymbol);
                if (!intersection.isEmpty()) {
                    newFinalStates.add(stateForSymbol.toString());
                }

                if (stateForSymbol.isEmpty()) {
                    stateForSymbol.add("-");
                }

                temp.put(symbol, stateForSymbol);
            }
            tableAutomaton.put(currentStates.toString(), new HashMap<>(temp));
        }

        //System.out.println(tableAutomaton);

        Map<String, String> dictionary = new HashMap<>();

        int i = 1;
        for (String states : tableAutomaton.keySet()) {
            dictionary.put(states.toString(), String.valueOf(i));
            i++;
        }

        if (showDictionary) {
            System.out.println("New state's names:");
            for (String states : dictionary.keySet()) {
                System.out.println(states + ": " + dictionary.get(states));
            }
        }

        dictionary.put("[-]", "-");

        Map<String, Map<String, String>> renameTableAutomaton = new HashMap<>();
        for (String states : tableAutomaton.keySet()) {
            Map<String, String> temp = new HashMap<>();
            for (String symbol : tableAutomaton.get(states).keySet()) {
                temp.put(symbol, dictionary.get(tableAutomaton.get(states).get(symbol).toString()));
            }
            renameTableAutomaton.put(dictionary.get(states.toString()), new HashMap<>(temp));
        }

        //System.out.println(renameTableAutomaton);

        String newStartState = dictionary.get(Set.of(startState).toString());
        List<String> newAlphabet = new ArrayList<>(alphabet);
        List<String> newStates = new ArrayList<>(renameTableAutomaton.keySet());
        Set<String> newRenameFinalStates = new HashSet<>();
        for (String finalState : newFinalStates) {
            newRenameFinalStates.add(dictionary.get(finalState));
        }

        return new AutomatonDFA(newStates, newAlphabet, newStartState, newRenameFinalStates, renameTableAutomaton, AutomatonType.DFA);

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
                    String[] nextState = transitionTable.getOrDefault(state, Map.of()).get(symbol);
                    row.append(nextState != null ? collectionToString(nextState) : "-").append(" ");
                }
                writer.write(row.toString().trim());
                writer.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
