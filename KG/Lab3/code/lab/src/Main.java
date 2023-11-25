import javax.rmi.ssl.SslRMIClientSocketFactory;
import javax.swing.*;
import java.util.ArrayList;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        ArrayList<Pixel> points = Methods.brezenheim(5,5,13,9);
        for (int i = 0; i < points.size(); i++) {
            System.out.println(points.get(i).toString());
        }
        System.out.println("----------------------");
        ArrayList<Pixel> points1 = Methods.stepByStep(5,5,13,9);
        for (int i = 0; i < points1.size(); i++) {
            System.out.println(points1.get(i).toString());
        }
        MainFrame mainFrame = new MainFrame();
        mainFrame.setSize(400,100);
        mainFrame.setVisible(true);
    }
}