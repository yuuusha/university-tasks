package GetMessage;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ParamsGet {
    public Map<String, String> params;

    public ParamsGet(String[] args) {

        if (List.of(args).contains("<") && List.of(args).contains(">")) {
            for (int i = 0; i < args.length; i++) {
                if (args[i].equals("<")) {
                    args[i] = "-s";
                }
                if (args[i].equals(">")) {
                    args[i] = "-m";
                }
            }
        }

        Map<String, String> parameters = new HashMap<>();
        for (int i = 0; i < args.length; i++) {
            if (args[i].startsWith("-")) {
                if (i + 1 < args.length && !args[i + 1].startsWith("-")) {
                    parameters.put(args[i], args[i + 1]);
                    i++;
                } else {
                    parameters.put(args[i], null);
                }
            }
        }

        if (parameters.containsKey("-h") || parameters.containsKey("--help")) {
            System.out.println("Программа восстанавливает  сообщение из  стегоконтейнера точно\n" +
                    "бит в бит.\n" +
                    "-m и --message – путь к файлу, в который нужно записать сообщение в том\n" +
                    "виде,  в  котором оно было до встраивания.  Если не  указан,  то  сообщение\n" +
                    "выводится в стандартный поток вывода.\n" +
                    "-s  и  --stego  –   путь   к  стегоконтейнеру,   Если   не   указан,   то   содержимое\n" +
                    "стегоконтейнера передаётся через стандартный поток ввода.\n" +
                    "-h и  --help – вывести справку о том, как использовать программу и что она\n" +
                    "делает.");
        }

        if (!parameters.containsKey("-m") && !parameters.containsKey("--message")) {
            parameters.put("-m", "std");
        }
        if (!parameters.containsKey("-s") && !parameters.containsKey("--stego")) {
            parameters.put("-s", "std");
        }

        params = new HashMap<>(parameters);
    }

    public String getMessage() {
        if (params.containsKey("-message")) {
            return params.get("--message");
        }
        return params.get("-m");
    }

    public String getStego() {
        if (params.containsKey("--stego")) {
            return params.get("--stego");
        }
        return params.get("-s");
    }
}
