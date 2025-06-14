package lab3;

import java.util.ArrayList;
import java.util.List;

public class PostfixList {
    List<PostfixEntry> postfixEntryList;

    public PostfixList() {
        this.postfixEntryList = new ArrayList<>();
    }

    public PostfixList(List<PostfixEntry> postfixEntryList) {
        this.postfixEntryList = postfixEntryList;
    }

    public int size() {
        return postfixEntryList.size();
    }

    public int addCommand(Command command) {
        PostfixEntry postfixEntry = new PostfixEntry(EntryType.COMMAND, command);
        postfixEntryList.add(postfixEntry);
        return postfixEntryList.size() - 1;
    }

    public int addVar(String name) {
        PostfixEntry postfixEntry = new PostfixEntry(EntryType.VAR, null, name);
        postfixEntryList.add(postfixEntry);
        return postfixEntryList.size() - 1;
    }

    public int addConst(int indConst) {
        PostfixEntry postfixEntry = new PostfixEntry(EntryType.CONST, null, indConst);
        postfixEntryList.add(postfixEntry);
        return postfixEntryList.size() - 1;
    }

    public int addAddress(int indAddress) {
        PostfixEntry postfixEntry = new PostfixEntry(EntryType.ADDRESS, null, indAddress);
        postfixEntryList.add(postfixEntry);
        return postfixEntryList.size() - 1;
    }

    public void setAddress(int indCommand, int address) {
        postfixEntryList.get(indCommand).setValue(address);
    }

    @Override
    public String toString() {
        return "PostfixList{" +
                "postfixEntryList=" + postfixEntryList +
                '}';
    }

    public void print() {
        int maxNameWidth = "Наименование".length();
        int maxIndexWidth = "Индекс".length();

        for (int i = 0; i < postfixEntryList.size(); i++) {
            PostfixEntry entry = postfixEntryList.get(i);
            String nameColumn = getNameColumn(entry);
            maxNameWidth = Math.max(maxNameWidth, nameColumn.length());
            maxIndexWidth = Math.max(maxIndexWidth, String.valueOf(i).length());
        }

        String formatString = "| %-" + maxNameWidth + "s | %-" + maxIndexWidth + "s |%n";
        System.out.printf(formatString, "ПОЛИЗ", "Индекс");

        for (int i = 0; i < postfixEntryList.size(); i++) {
            PostfixEntry entry = postfixEntryList.get(i);
            String nameColumn = getNameColumn(entry);
            System.out.printf(formatString, nameColumn, i);
        }
    }

    private String getNameColumn(PostfixEntry entry) {
        return switch (entry.getEntryType()) {
            case VAR -> entry.getName() != null ? entry.getName() : "N/A";
            case CONST, ADDRESS -> entry.getValue() != null ? entry.getValue().toString() : "N/A";
            case COMMAND -> entry.getCommand() != null ? entry.getCommand().toString() : "N/A";
            default -> "N/A";
        };
    }

    public List<PostfixEntry> getPostfixEntryList() {
        return postfixEntryList;
    }
}
