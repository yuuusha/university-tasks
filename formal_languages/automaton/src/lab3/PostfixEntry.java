package lab3;

public class PostfixEntry {
    private EntryType entryType;
    private Command command;
    private Integer value;
    private String name;

    public String getName() {
        return name;
    }

    public PostfixEntry(EntryType entryType, Command command) {
        this.entryType = entryType;
        this.command = command;
        this.value = null;
    }
    public PostfixEntry(EntryType entryType, Integer value) {
        this.entryType = entryType;
        this.command = null;
        this.value = value;
    }

    public PostfixEntry(EntryType entryType, Command command, Integer value) {
        this.entryType = entryType;
        this.command = command;
        this.value = value;
    }

    public PostfixEntry(EntryType entryType, Command command, String name) {
        this.entryType = entryType;
        this.command = command;
        this.name = name;
    }

    public EntryType getEntryType() {
        return entryType;
    }

    public void setEntryType(EntryType entryType) {
        this.entryType = entryType;
    }

    public Integer getValue() {
        return value;
    }

    public void setValue(Integer value) {
        this.value = value;
    }

    public Command getCommand() {
        return command;
    }

    public void setCommand(Command command) {
        this.command = command;
    }

    @Override
    public String toString() {
        return "PostfixEntry{" +
                "entryType=" + entryType +
                ", command=" + command +
                ", value=" + value +
                ", name=" + name +
                '}';
    }
}
