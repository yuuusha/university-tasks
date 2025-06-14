package lab3;

public enum EntryType {
    COMMAND,
    VAR,
    CONST,
    ADDRESS;

    @Override
    public String toString() {
        return switch (this) {
            case COMMAND -> "COMMAND";
            case VAR -> "VAR";
            case CONST -> "CONST";
            case ADDRESS -> "ADDRESS";
            default -> super.toString();
        };
    }
}
