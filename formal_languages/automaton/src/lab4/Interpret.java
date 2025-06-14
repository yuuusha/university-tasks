package lab4;

import lab3.EntryType;
import lab3.PostfixEntry;
import lab3.SyntaxAnalyzerInnerCode;

import java.util.*;

public class Interpret {

    private Stack<PostfixEntry> stack;
    private List<PostfixEntry> postfixEntryList;
    private Map<String, Integer> variable;

    public Map<String, Integer> getVariable() {
        return variable;
    }

    public Interpret() {
        stack = new Stack<>();
        postfixEntryList = new ArrayList<>();
        variable = new HashMap<>();
    }

    public void start(String program, Map<String, Integer> variable) {

        SyntaxAnalyzerInnerCode analyzer = new SyntaxAnalyzerInnerCode();
        boolean res = analyzer.start(program);
        if (!res) {
            throw new RuntimeException("Ошибка при работе синтаксического анализатора");
        }

        analyzer.getPostfixList().print();

        postfixEntryList = new ArrayList<>(analyzer.getPostfixList().getPostfixEntryList());
        this.variable = variable;
        stack = new Stack<>();

        System.out.println("| Индекс | Значения переменных | Элемент | Стек");

        int iPrev;

        for (int i = 0; i < postfixEntryList.size(); ) {

            iPrev = i;

            PostfixEntry entry = postfixEntryList.get(i);

            if (entry.getEntryType() != EntryType.COMMAND) {
                stack.add(entry);
                i++;
            } else {
                switch (entry.getCommand()) {
                    case JMP -> {
                        i = popAddress();
                    }
                    case JZ -> {
                        int address = popAddress();
                        int condition = popValue();
                        if (condition == 0) {
                            i = address;
                        } else {
                            i++;
                        }
                    }
                    case SET -> {
                        int value = popValue();
                        String var = popVar();
                        variable.put(var, value);
                        i++;
                    }
                    case ADD -> {
                        int var1 = popValue();
                        int var2 = popValue();
                        addValue(var1 + var2);
                        i++;
                    }
                    case SUB -> {
                        int var1 = popValue();
                        int var = popValue();
                        addValue(var - var1);
                        i++;
                    }
                    case NOT -> {
                        int value = popValue();
                        addValue((value > 0) ? 0 : 1);
                        i++;
                    }
                    case CMPE -> {
                        int var1 = popValue();
                        int var2 = popValue();
                        addValue((var1 == var2) ? 1 : 0);
                        i++;
                    }
                    case CMPNE -> {
                        int var1 = popValue();
                        int var2 = popValue();
                        addValue((var1 != var2) ? 1 : 0);
                        i++;
                    }
                    case CMPL -> {
                        int var2 = popValue();
                        int var1 = popValue();
                        addValue((var1 < var2) ? 1 : 0);
                        i++;
                    }
                    case CMPLE -> {
                        int var2 = popValue();
                        int var1 = popValue();
                        addValue((var1 <= var2) ? 1 : 0);
                        i++;
                    }
                    case CMPG -> {
                        int var2 = popValue();
                        int var1 = popValue();
                        addValue((var1 > var2) ? 1 : 0);
                        i++;
                    }
                    case CMPGE -> {
                        int var2 = popValue();
                        int var1 = popValue();
                        addValue((var1 >= var2) ? 1 : 0);
                        i++;
                    }
                }
            }
            printState(iPrev, entry);
        }

    }

    public int popValue() {
        PostfixEntry entry = stack.pop();
        if (entry.getEntryType() == EntryType.CONST) {
            return entry.getValue();
        }
        else if (entry.getEntryType() == EntryType.VAR) {
            return variable.get(entry.getName());
        }
        else {
            throw new RuntimeException("Ошибка интерпретатора");
        }
    }

    public String popVar() {
        PostfixEntry entry = stack.pop();
        if (entry.getEntryType() == EntryType.VAR) {
            return entry.getName();
        } else {
            throw new RuntimeException("Ошибка интерпретатора");
        }
    }

    public int popAddress() {
        PostfixEntry entry = stack.pop();
        if (entry.getEntryType() == EntryType.ADDRESS) {
            return entry.getValue();
        }
        else {
            throw new RuntimeException("Ошибка интерпретатора");
        }
    }

    public void addValue(int value) {
        PostfixEntry entry = new PostfixEntry(EntryType.CONST, value);
        stack.add(entry);
    }

    public void printState(int i, PostfixEntry element) {

        int indexWidth = "Индекс".length();
        int variableWidth = "Значения переменных".length();
        int elementWidth = "Элемент".length();
        int stackWidth = "Стек".length();

        String formatString = "| %-" + indexWidth + "s | %-" + variableWidth + "s | %-" + elementWidth + "s | %-" + stackWidth + "s %n";

        StringBuilder variableOutput = new StringBuilder();
        for (Map.Entry<String, Integer> entry : variable.entrySet()) {
            if (!variableOutput.isEmpty()) {
                variableOutput.append(", ");
            }
            variableOutput.append(entry.getKey()).append("=").append(entry.getValue());
        }

        StringBuilder stackOutput = new StringBuilder();
        for (PostfixEntry entry : stack) {
            if (!stackOutput.isEmpty()) {
                stackOutput.append(", ");
            }
            stackOutput.append(getNameColumn(entry));
        }

        System.out.printf(formatString, i, variableOutput, getNameColumn(element), stackOutput);
    }

    private String getNameColumn(PostfixEntry entry) {
        return switch (entry.getEntryType()) {
            case VAR -> entry.getName() != null ? entry.getName() : "N/A";
            case CONST, ADDRESS -> entry.getValue() != null ? entry.getValue().toString() : "N/A";
            case COMMAND -> entry.getCommand() != null ? entry.getCommand().toString() : "N/A";
            default -> "N/A";
        };
    }

}
