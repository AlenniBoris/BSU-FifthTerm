import javax.swing.*;
import java.awt.*;

public class MainFrame extends JFrame {
    private ImagePanel imagePanel;
    private ControlPanel controlPanel;
    public MainFrame(){
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        imagePanel = new ImagePanel(this);
        add(imagePanel);

        controlPanel = new ControlPanel(this);
        add(controlPanel, BorderLayout.SOUTH);
    }

    public ImagePanel getImagePanel() {
        return imagePanel;
    }

    public ControlPanel getControlPanel() {
        return controlPanel;
    }
}
