package lab1;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class LexicalAnalyzer {
    List<Lexeme> lexemes;

    public List<Lexeme> getLexemes() {
        return lexemes;
    }

    public boolean start(String input) {

        input = input + '\n';

        lexemes = new ArrayList<>();

        State currentState = State.START;
        State previousState;

        boolean canAdd;

        StringBuilder currentLexeme = new StringBuilder();
        StringBuilder nextLexeme = new StringBuilder();

        int index = 0;
        int pos = index;

        while (currentState != State.ERROR) {

            previousState = currentState;
            canAdd = true;

            if (index == input.length()) {
                currentState = State.FINAL;
                break;
            }

            char currentSymbol = input.charAt(index);

            switch (currentState) {

                case START: {

                    if (Character.isWhitespace(currentSymbol)) {
                        currentState = State.START;
                    } else if (Character.isDigit(currentSymbol)) {
                        currentState = State.CONSTANT;
                    } else if (Character.isLetter(currentSymbol)) {
                        currentState = State.IDENTIFIER;
                    } else if (currentSymbol == '>' || currentSymbol == '<') {
                        currentState = State.COMPARISON;
                    } else if (currentSymbol == '+' || currentSymbol == '-') {
                        currentState = State.ARITHMETIC_OPERATION;
                    } else if (currentSymbol == '=') {
                        currentState = State.ASSIGMENT;
                    } else {
                        currentState = State.ERROR;
                    }

                    canAdd = false;
                    pos = index;

                    if (!Character.isWhitespace(currentSymbol)) {
                        currentLexeme.append(currentSymbol);
                    }

                    break;
                }

                case COMPARISON: {

                    if (Character.isWhitespace(currentSymbol)) {
                        currentState = State.START;
                    } else if (currentSymbol == '=') {
                        currentState = State.START;
                        currentLexeme.append(currentSymbol);
                    } else if (currentSymbol == '>') {
                        currentState = State.START;
                        currentLexeme.append(currentSymbol);
                    } else if (Character.isLetter(currentSymbol)) {
                        currentState = State.IDENTIFIER;
                        nextLexeme.append(currentSymbol);
                    } else if (Character.isDigit(currentSymbol)) {
                        currentState = State.CONSTANT;
                        nextLexeme.append(currentSymbol);
                    } else {
                        currentState = State.ERROR;
                        canAdd = false;
                    }

                    break;
                }

                case ASSIGMENT: {
                    if (currentSymbol == '=') {
                        currentState = State.COMPARISON;
                        currentLexeme.append(currentSymbol);
                    } else if (Character.isWhitespace(currentSymbol)) {
                        currentState = State.START;
                    } else if (Character.isLetter(currentSymbol)) {
                        currentState = State.IDENTIFIER;
                        nextLexeme.append(currentSymbol);
                    } else if (Character.isDigit(currentSymbol)) {
                        currentState = State.CONSTANT;
                        nextLexeme.append(currentSymbol);
                    } else {
                        currentState = State.ERROR;
                        nextLexeme.append(currentSymbol);
                    }

                    break;
                }

                case CONSTANT: {
                    if (Character.isWhitespace(currentSymbol)) {
                        currentState = State.START;
                    } else if (Character.isDigit(currentSymbol)) {
                        canAdd = false;
                        currentState = State.CONSTANT;
                        currentLexeme.append(currentSymbol);
                    } else if (currentSymbol == '<' || currentSymbol == '>') {
                        currentState = State.COMPARISON;
                        nextLexeme.append(currentSymbol);
                    } else if (currentSymbol == '=') {
                        currentState = State.ASSIGMENT;
                        nextLexeme.append(currentSymbol);
                    } else if (currentSymbol == '+' || currentSymbol == '-') {
                        currentState = State.ARITHMETIC_OPERATION;
                        nextLexeme.append(currentSymbol);
                    } else {
                        currentState = State.ERROR;
                        canAdd = false;
                    }

                    break;
                }

                case IDENTIFIER: {
                    if (Character.isWhitespace(currentSymbol)) {
                        currentState = State.START;
                    } else if (Character.isDigit(currentSymbol) || Character.isLetter(currentSymbol)) {
                        currentState = State.IDENTIFIER;
                        canAdd = false;
                        currentLexeme.append(currentSymbol);
                    } else if (currentSymbol == '>' || currentSymbol == '<') {
                        currentState = State.COMPARISON;
                        nextLexeme.append(currentSymbol);
                    } else if (currentSymbol == '=') {
                        currentState = State.ASSIGMENT;
                        nextLexeme.append(currentSymbol);
                    } else if (currentSymbol == '+' || currentSymbol == '-') {
                        currentState = State.ARITHMETIC_OPERATION;
                        nextLexeme.append(currentSymbol);
                    } else {
                        currentState = State.ERROR;
                        canAdd = false;
                    }

                    break;
                }

                case State.ARITHMETIC_OPERATION: {
                    if (Character.isWhitespace(currentSymbol)) {
                        currentState = State.START;
                    } else if (Character.isLetter(currentSymbol)) {
                        currentState = State.IDENTIFIER;
                        nextLexeme.append(currentSymbol);
                    } else if (Character.isDigit(currentSymbol)) {
                        currentState = State.CONSTANT;
                        nextLexeme.append(currentSymbol);
                    } else if (currentSymbol == '-' || currentSymbol == '+') {
                        currentState = State.ARITHMETIC_OPERATION;
                        nextLexeme.append(currentSymbol);
                    } else {
                        currentState = State.ERROR;
                        canAdd = false;
                    }

                    break;
                }

            }

            if (canAdd) {
                addLexeme(previousState, currentLexeme.toString(), pos);
                currentLexeme = new StringBuilder(nextLexeme.toString());
                nextLexeme = new StringBuilder();
            }

            if (currentState == State.ERROR) {
                throw new RuntimeException("Ошибка лексического анализа: " + currentLexeme + " на позиции " + pos);
            }

            index++;
        }

        return currentState == State.FINAL;

    }

    private void addLexeme(State prevState, String value, int pos) {
        LexemeType lexemeType = LexemeType.UNDEFINED;
        LexemeCategory lexemeCategory = LexemeCategory.UNDEFINED;

        if (prevState == State.ARITHMETIC_OPERATION) {
            lexemeType = LexemeType.ARITHMETIC_OPERATION;
            lexemeCategory = LexemeCategory.SPECIAL_SYMBOL;
        } else if (prevState == State.ASSIGMENT) {
            lexemeCategory = LexemeCategory.SPECIAL_SYMBOL;
            if (Objects.equals(value, "==")) {
                lexemeType = LexemeType.RELATION;
            } else {
                lexemeType = LexemeType.ASSIGMENT;
            }
        }
        else if (prevState == State.CONSTANT) {
            lexemeType = LexemeType.UNDEFINED;
            lexemeCategory = LexemeCategory.CONSTANT;
        }
        else if (prevState == State.COMPARISON) {
            lexemeType = LexemeType.RELATION;
            lexemeCategory = LexemeCategory.SPECIAL_SYMBOL;
        }
        else if (prevState == State.IDENTIFIER) {

            boolean isKeyword = true;

            value = value.toLowerCase();

            if (value.equalsIgnoreCase("do")) {
                lexemeType = LexemeType.DO;
            } else if (value.equalsIgnoreCase( "loop")) {
                lexemeType = LexemeType.LOOP;
            } else if (value.equalsIgnoreCase("until")) {
                lexemeType = LexemeType.UNTIL;
            } else {
                lexemeType = LexemeType.UNDEFINED;
                isKeyword = false;
            }

            if (isKeyword) {
                lexemeCategory = LexemeCategory.KEYWORD;
            } else {
                lexemeCategory = LexemeCategory.IDENTIFIER;
            }
        }

        Lexeme lexeme = new Lexeme(lexemeType, lexemeCategory, value, pos);

        if (!lexeme.getValue().isEmpty()) {
            lexemes.add(lexeme);
        }
    }


}
