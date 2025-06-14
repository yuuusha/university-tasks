package lab1;

public enum LexemeType {
    DO,
    LOOP,
    UNTIL,
    RELATION,
    ARITHMETIC_OPERATION,
    ASSIGMENT,
    UNDEFINED;

    @Override
    public String toString() {
        return switch (this) {
            case DO -> "do";
            case LOOP -> "loop";
            case UNTIL -> "until";
            case RELATION -> "relation";
            case ARITHMETIC_OPERATION -> "arithmetic_operation";
            case ASSIGMENT -> "assignment";
            case UNDEFINED -> "-";
            default -> super.toString();
        };
    }
}
