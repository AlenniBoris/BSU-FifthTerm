import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainFrame extends JFrame {
    private JButton btn;
    private JColorChooser colorChooser;
    public MainFrame() throws HeadlessException {
        btn = new JButton("Button");
        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                colorChooser = new JColorChooser();
                colorChooser.setVisible(true);
            }
        });
        add(btn);
    }
}
