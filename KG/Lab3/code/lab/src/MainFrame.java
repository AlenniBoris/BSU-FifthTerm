import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Locale;
import java.util.concurrent.atomic.AtomicLong;

public class MainFrame extends JFrame {
    private MainFrame frame;
    private JLabel brezTime;
    private JLabel stepTime;
    public MainFrame(){
        setLayout(new GridLayout(3,1));
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.frame = this;
        JPanel labels = new JPanel(new GridLayout(1,4));
        JTextField x0 = new JTextField("x0");
        JTextField x1 = new JTextField("x1");
        JTextField y0 = new JTextField("y0");
        JTextField y1 = new JTextField("y1");
        labels.add(x0);
        labels.add(y0);
        labels.add(x1);
        labels.add(y1);
        add(labels);
        JPanel buttons = new JPanel(new GridLayout(1,2));
        JButton brezenheim = new JButton("Brezenheim");
        brezenheim.addActionListener(e -> {
            try{
                int startX = Integer.parseInt(x0.getText());
                int endX = Integer.parseInt(x1.getText());
                int startY = Integer.parseInt(y0.getText());
                int endY = Integer.parseInt(y1.getText());
                int max1 = Math.max(Math.abs(startX),Math.abs(endX));
                int max2 = Math.max(Math.abs(startY),Math.abs(endY));
                int max = Math.max(max1, max2);
                ArrayList<Pixel> list = Methods.brezenheim(startX, startY, endX, endY);
                long start = System.currentTimeMillis();
                GraphPlotter brezenheim1 = new GraphPlotter(list, "Brezenheim", max);
                long timeB = System.currentTimeMillis() - start;
                brezTime.setText(Long.toString(timeB) + "ms");
                brezenheim1.setVisible(true);
            }catch (Exception exception) {
                JOptionPane.showMessageDialog(frame, "Check inputs");
            }
        });

        JButton step = new JButton("Step by step");
        step.addActionListener(e -> {
            try{
                int startX = Integer.parseInt(x0.getText());
                int endX = Integer.parseInt(x1.getText());
                int startY = Integer.parseInt(y0.getText());
                int endY = Integer.parseInt(y1.getText());
                int max1 = Math.max(Math.abs(startX),Math.abs(endX));
                int max2 = Math.max(Math.abs(startY),Math.abs(endY));
                int max = Math.max(max1, max2);
                long start = System.currentTimeMillis();
                ArrayList<Pixel> list = Methods.stepByStep(startX, startY, endX, endY);
                long timeS = System.currentTimeMillis() - start;
                stepTime.setText(Long.toString(timeS) + "ms");
                GraphPlotter step_by_step = new GraphPlotter(list, "Step by step", max);
                step_by_step.setVisible(true);
            }catch (Exception exception) {
                JOptionPane.showMessageDialog(frame, "Check inputs");
            }
        });
        buttons.add(brezenheim);
        buttons.add(step);
        add(buttons);

        JPanel times = new JPanel(new GridLayout(1,2));
        brezTime = new JLabel("Time brez");
        stepTime = new JLabel("Time step");
        times.add(brezTime);
        times.add(stepTime);

        add(times);
    }
}
