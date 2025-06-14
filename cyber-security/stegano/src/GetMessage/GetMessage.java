package GetMessage;


public class GetMessage {

    public static void main(String[] args) {

        ParamsGet params = new ParamsGet(args);

        String stegoPath = params.getStego();
        Container container = new Container(stegoPath);

        String messagePath = params.getMessage();
        container.process(messagePath);

    }
}
