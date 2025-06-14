package lab3;

import lab1.Lexeme;
import lab1.LexemeCategory;
import lab1.LexemeType;
import lab1.LexicalAnalyzer;
import lab2.ExtraSymbolsException;
import lab2.WrongLexemeException;

import java.util.List;
import java.util.ListIterator;

public class SyntaxAnalyzerInnerCode {
    private PostfixList postfixList;

    public PostfixList getPostfixList() {
        return postfixList;
    }

    private ListIterator<Lexeme> lexemesIterator;
    private Lexeme curLexeme;

    public boolean start(String input) {

        LexicalAnalyzer lexicalAnalyzer = new LexicalAnalyzer();
        boolean res = lexicalAnalyzer.start(input);
        if (!res) {
            throw new RuntimeException("Errors while lexical analysis");
        }

        List<Lexeme> lexemes = lexicalAnalyzer.getLexemes();
        Lexeme.printLexemeTable(lexemes);

        postfixList = new PostfixList();
        lexemesIterator = lexemes.listIterator();

        return isLoopStatement(lexemes);
    }

    private boolean isLoopStatement(List<Lexeme> lexemes) {

        if (lexemes.isEmpty()) {
            return false;
        }

        int cycleStartAddress = postfixList.size(); // сохраняем адрес начала цикла

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();
            if (curLexeme.getLexemeType() != LexemeType.DO) {
                throw new WrongLexemeException(LexemeType.DO.toString(), curLexeme.getPos());
            }
        }
        else {
            throw new WrongLexemeException(LexemeType.DO.toString(), curLexeme.getPos());
        }

        if (!isAdvancedStatement()) {
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

        // сформирована часть ПОЛИЗа, вычисляющая условие цикла
        postfixList.addCommand(Command.NOT); //заносим команду NOT для until
        int indJmp = postfixList.addAddress(cycleStartAddress); //заносим адрес начала цикла
        //адреса условного перехода
        postfixList.addCommand(Command.JZ); //заносим команду условного перехода

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

                // вычисляем команду
                Command command;
                switch (curLexeme.getValue()) {
                    case "<" -> command = Command.CMPL;
                    case "<=" -> command = Command.CMPLE;
                    case ">" -> command = Command.CMPG;
                    case ">=" -> command = Command.CMPGE;
                    case "==" -> command = Command.CMPE;
                    case "<>" -> command = Command.CMPNE;
                    default -> throw new WrongLexemeException(LexemeType.RELATION.toString(), curLexeme.getPos());
                }

                if (!isOperand()) {
                    return false;
                }

                // добавляем команду в полиз
                postfixList.addCommand(command);

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

            // добавляем операнд в полиз
            if (curLexeme.getLexemeCategory() == LexemeCategory.CONSTANT) {
                postfixList.addConst(Integer.parseInt(curLexeme.getValue()));
            } else {
                postfixList.addVar(curLexeme.getValue());
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

            // заносим переменную в полиз
            postfixList.addVar(curLexeme.getValue());

            if (lexemesIterator.hasNext()) {
                curLexeme = lexemesIterator.next();

                if (curLexeme.getLexemeType() != LexemeType.ASSIGMENT) {
                    throw new WrongLexemeException(LexemeType.ASSIGMENT.toString(), curLexeme.getPos());
                }

                if (!isArithmeticOperation()) {
                    return false;
                }

                // ПОЛИЗ для выражения уже сформирован
                postfixList.addCommand(Command.SET); // заносим в ПОЛИЗ команду присваивания

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

                // вычисляем команду
                Command command;
                switch (curLexeme.getValue()) {
                    case "+" -> command = Command.ADD;
                    case "-" -> command = Command.SUB;
                    default -> throw new WrongLexemeException(LexemeType.ARITHMETIC_OPERATION.toString(), curLexeme.getPos());
                }

                if (!isOperand()) {
                    return false;
                }

                // добавляем команду в полиз
                postfixList.addCommand(command);

                curLexeme = lexemesIterator.next();
            }

            curLexeme = lexemesIterator.previous();
        }

        return true;
    }

    public boolean isAdvancedStatement() {
        if (!isStatement()) {
            return false;
        }

        if (lexemesIterator.hasNext()) {
            curLexeme = lexemesIterator.next();

            while (curLexeme.getLexemeCategory() == LexemeCategory.IDENTIFIER) {
                curLexeme = lexemesIterator.previous();

                if (!isStatement()) {
                    return false;
                }

                curLexeme = lexemesIterator.next();
            }
            curLexeme = lexemesIterator.previous();
        }

        return true;
    }

}
