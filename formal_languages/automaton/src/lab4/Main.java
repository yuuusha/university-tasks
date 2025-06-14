package lab4;

import lab1.Lexeme;
import lab1.LexicalAnalyzer;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

public class Main {

    public static void main(String[] args) {

        String programPath = "src/lab4/program.txt";
        String variablePath = "src/lab4/variables.txt";

        VariableReader variableReader = new VariableReader();
        variableReader.readFile(variablePath);
        Map<String, Integer> variables = new HashMap<>(variableReader.getVariableMap());

        String program;
        try {
            program = Files.readString(Path.of(programPath));
        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла: " + e.getMessage());
            return;
        }

        Interpret interpret = new Interpret();
        interpret.start(program, variables);

    }

}
