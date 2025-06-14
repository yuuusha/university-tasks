package lab2;

import lab1.Lexeme;
import lab1.LexemeCategory;
import lab1.LexemeType;
import lab1.LexicalAnalyzer;

import java.util.List;
import java.util.ListIterator;

public class SyntaxAnalyzer {

    private ListIterator<Lexeme> lexemesIterator;
    private Lexeme curLexeme;

    public boolean start(String input) {

        LexicalAnalyzer lexicalAnalyzer = new LexicalAnalyzer();
        boolean res = lexicalAnalyzer.start(input);
        if (!res) {
            throw new RuntimeException("Ошибка при работе лексического анализатора");
        }

        List<Lexeme> lexemes = lexicalAnalyzer.getLexemes();
        Lexeme.printLexemeTable(lexemes);

        lexemesIterator = lexemes.listIterator();

        return isLoopStatement(lexemes);
    }

    private boolean isLoopStatement(List<Lexeme> lexemes) {

        if (lexemes.isEmpty()) {
            return false;
        }

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();
            if (curLexeme.getLexemeType() != LexemeType.DO) {
                throw new WrongLexemeException(LexemeType.DO.toString(), curLexeme.getPos());
            }
        }
        else {
            throw new WrongLexemeException(LexemeType.DO.toString(), curLexeme.getPos());
        }

        if (!isStatement()) {
            return false;
        }

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();
            if (curLexeme.getLexemeType() != LexemeType.LOOP) {
                throw new WrongLexemeException(LexemeType.LOOP.toString(), curLexeme.getPos());
            }
        }
        else {
            throw new WrongLexemeException(LexemeType.LOOP.toString(), curLexeme.getPos());
        }

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();
            if (curLexeme.getLexemeType() != LexemeType.UNTIL) {
                throw new WrongLexemeException(LexemeType.UNTIL.toString(), curLexeme.getPos());
            }
        }
        else {
            throw new WrongLexemeException(LexemeType.UNTIL.toString(), curLexeme.getPos());
        }

        if (!isCondition()) {
            return false;
        }

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();
            throw new ExtraSymbolsException(curLexeme.getPos());
        }

        return true;
    }

    private boolean isCondition() {

        if (!isOperand()) {
            return false;
        }

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();
            if (curLexeme.getLexemeType() == LexemeType.RELATION) {
                if (!isOperand()) {
                    return false;
                }
            } else {
                curLexeme = lexemesIterator.previous();
            }
        }

        return true;

    }

    private boolean isOperand() {

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();
            if (curLexeme.getLexemeCategory() != LexemeCategory.CONSTANT && curLexeme.getLexemeCategory() != LexemeCategory.IDENTIFIER) {
                throw new WrongLexemeException(LexemeCategory.IDENTIFIER.toString(), LexemeCategory.CONSTANT.toString(), curLexeme.getPos());
            }
        } else {
            throw new WrongLexemeException(LexemeCategory.IDENTIFIER.toString(), LexemeCategory.CONSTANT.toString(), curLexeme.getPos());
        }

        return true;
    }

    private boolean isStatement() {

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();

            if (curLexeme.getLexemeCategory() != LexemeCategory.IDENTIFIER) {
                throw new WrongLexemeException(LexemeCategory.IDENTIFIER.toString(), curLexeme.getPos());
            }

            if (lexemesIterator.hasNext()) {
                curLexeme = lexemesIterator.next();

                if (curLexeme.getLexemeType() != LexemeType.ASSIGMENT) {
                    throw new WrongLexemeException(LexemeType.ASSIGMENT.toString(), curLexeme.getPos());
                }

                if (!isArithmeticOperation()) {
                    return false;
                }
            } else {
                throw new WrongLexemeException(LexemeType.ASSIGMENT.toString(), curLexeme.getPos());
            }
        } else {
            throw new WrongLexemeException(LexemeCategory.IDENTIFIER.toString(), curLexeme.getPos());
        }

        return true;

    }

    private boolean isArithmeticOperation() {

        if (!isOperand()) {
            return false;
        }

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();

            while (curLexeme.getLexemeType() == LexemeType.ARITHMETIC_OPERATION) {
                if (!isOperand()) {
                    return false;
                }
                curLexeme = lexemesIterator.next();
            }

            curLexeme = lexemesIterator.previous();
        }

        return true;
    }

}
