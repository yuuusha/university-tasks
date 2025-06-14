package automatons;

public enum AutomatonType {
    DFA,
    NFA,
    eNFA;

    public String getDescription() {
        return switch (this) {
            case DFA -> "Deterministic Finite Automaton";
            case NFA -> "Non-deterministic Finite Automaton";
            case eNFA -> "Non-deterministic Finite Automaton with epsilon transitions";
            default -> "Unknown Type";
        };
    }

    public static AutomatonType fromString(String type) {
        return switch (type.trim().toLowerCase()) {
            case "dfa" -> DFA;
            case "nfa" -> NFA;
            case "enfa" -> eNFA;
            default -> throw new IllegalArgumentException("Unsupported automaton type: " + type);
        };
    }
}