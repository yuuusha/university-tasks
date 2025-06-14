package automatons;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class AutomatonENFA {
    private final AutomatonType automatonType;
    private final List<String> states;
    private final List<String> alphabet;
    private final String startState;
    private final Set<String> finalStates;
    private final Map<String, Map<String, String[]>> transitionTable;

    public AutomatonENFA(List<String> states, List<String> alphabet, String startState, Set<String> finalStates, Map<String, Map<String, String[]>> transitionTable, AutomatonType automatonType) {
        this.states = states;
        this.alphabet = alphabet;
        this.startState = startState;
        this.finalStates = finalStates;
        this.transitionTable = transitionTable;
        this.automatonType = automatonType;
    }

    public static AutomatonENFA readFromFile(String filePath) throws IOException {

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
        return new AutomatonENFA(new ArrayList<>(states), new ArrayList<>(alphabet), startState, new HashSet<>(finalStates), new HashMap<>(transitionTable), automatonType);
    }

    public boolean accepts(String input) {

        HashSet<String> currentStates = new HashSet<>();
        currentStates.add(startState);

        if (input.isEmpty()) {
            System.out.println("Epsilon trasition! " + startState + " -> " + getLoopback(startState));
            currentStates.addAll(getLoopback(startState));
        }

        for (char symbol : input.toCharArray()) {
            String symbolStr = String.valueOf(symbol);
            if (!alphabet.contains(symbolStr)) {
                throw new IllegalArgumentException("Input contains invalid symbol: " + symbolStr);
            }

            try {
                for (String state : currentStates) {
                    System.out.println("Epsilon transitions! " + state + " -> " + getLoopback(state));
                    currentStates.addAll(getLoopback(state));
                }

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
                resString.append(", ");
            }
            resString.append(obj);
        }
        return resString.toString();
    }

    private Set<String> getLoopback(String state) {

        Stack<String> stack = new Stack<>();
        Set<String> wasHere = new HashSet<>();

        stack.add(state);

        while (!stack.isEmpty()) {
            String cur = stack.pop();

            wasHere.add(cur);
            List<String> temp = new ArrayList<>();

            if (!Arrays.toString(transitionTable.get(cur).get("ε")).contains("-")) {
                temp = List.of(transitionTable.get(cur).get("ε"));
            }

            for (String added : temp) {
                if (!wasHere.contains(added)) {
                    stack.add(added);
                }
            }
        }

        return new HashSet<>(wasHere);
    }

    public AutomatonNFA createNFA() {
        Map<String, Set<String>> loopbacks = new HashMap<>();

        for (String state : transitionTable.keySet()) {
            if (!Arrays.toString(transitionTable.get(state).get("ε")).contains("-")) {
                loopbacks.put(state, getLoopback(state));
            }
        }

        Set<String> newFinalStates = new HashSet<>(finalStates);
        for (String state : loopbacks.keySet()) {
            Set<String> temp = new HashSet<>(finalStates);
            temp.retainAll(loopbacks.get(state));
            if (!temp.isEmpty()) {
                newFinalStates.add(state);
            }
        }

        Map<String, Map<String, String[]>> newTransitionTable = new HashMap<>();
        for (String states : transitionTable.keySet()) {
            for (String symbol : alphabet) {
                if (!symbol.equals("ε")) {
                    newTransitionTable.put(states, new HashMap<>(transitionTable.get(states)));
                }
            }
        }

        List<String> newAlphabet = new ArrayList<>(alphabet);
        newAlphabet.remove("ε");

        for (String loopbackState : loopbacks.keySet()) {
            for (String loopback : loopbacks.get(loopbackState)) {
                if (!loopback.equals(loopbackState)) {
                    for (String symbol : newAlphabet) {
                        Set<String> newAddedStates = new HashSet<>(Set.of(transitionTable.get(loopback).get(symbol)));
                        Set<String> oldStates = new HashSet<>(Set.of(newTransitionTable.get(loopbackState).get(symbol)));
                        oldStates.addAll(newAddedStates);
                        oldStates.remove("-");
                        if (oldStates.isEmpty()) {
                            oldStates.add("-");
                        }

                        newTransitionTable.get(loopbackState).put(symbol, oldStates.toArray(new String[0]));

                    }
                }
            }
        }

        return new AutomatonNFA(states, newAlphabet, startState, newFinalStates, newTransitionTable, AutomatonType.NFA);
    }
}
