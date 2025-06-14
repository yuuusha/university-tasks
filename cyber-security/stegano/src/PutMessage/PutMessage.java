package PutMessage;

public class PutMessage {
    public static void main(String[] args) {

        ParamsPut params = new ParamsPut(args);
        String messagePath = params.getMessage();

        Message message = new Message(messagePath);

        String containerPath = params.getContainer();
        Container container = new Container(containerPath);

        String stegoPath = params.getStego();
        container.process(message, stegoPath);

    }
}