import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class ImagePanel extends JPanel {
    private MainFrame mainFrame;
    private JPanel leftContainer;
    private JPanel rightContainer;

    private JTextField sizeField;

    private JPanel originalImage;
    private JPanel processedImage;
    private JLabel labelOr;
    private JLabel labelPr;
    private JLabel labelPr1;

    private JLabel operation;

    public ImagePanel(MainFrame mainFrame) {
        this.mainFrame = mainFrame;
        setLayout(new GridLayout(0, 2, 0, 3));

        leftContainer = new JPanel(new BorderLayout());
        sizeField = new JTextField("0*0");
        sizeField.setEditable(false);
        leftContainer.add(sizeField, BorderLayout.NORTH);
        originalImage = new JPanel(new BorderLayout());
        labelOr = new JLabel();
        leftContainer.add(originalImage);


        rightContainer = new JPanel(new BorderLayout());
        JPanel tempPanel = new JPanel(new GridLayout(1, 2, 0, 3));
        JTextField processed = new JTextField("Processed");
        processed.setEditable(false);
        operation = new JLabel("None");
        tempPanel.add(processed);
        tempPanel.add(operation);
        rightContainer.add(tempPanel, BorderLayout.NORTH);
        processedImage = new JPanel(new GridLayout(1, 1));
        labelPr = new JLabel();
        processedImage.add(labelPr);
        labelPr1 = new JLabel();

        rightContainer.add(processedImage);

        add(leftContainer);
        add(rightContainer);
    }

    public JPanel getLeftContainer() {
        return leftContainer;
    }

    public JLabel getOperation() {
        return operation;
    }

    public JPanel getRightContainer() {
        return rightContainer;
    }

    public JTextField getSizeField() {
        return sizeField;
    }

    public JPanel getOriginalImage() {
        return originalImage;
    }

    public JPanel getProcessedImage() {
        return processedImage;
    }

    public void setPicOrigin(BufferedImage bufferedImage) {
        int panelWidth = originalImage.getWidth();
        int panelHeight = originalImage.getHeight();

        if (panelWidth>0 && panelHeight>0){
            Image scaled = bufferedImage.getScaledInstance(panelWidth, panelHeight, Image.SCALE_SMOOTH);
            labelOr.setIcon(new ImageIcon(scaled));
        }
        originalImage.add(labelOr);
    }

    public void setPicProcessed(BufferedImage bufferedImage) {
        int panelWidth = processedImage.getWidth();
        int panelHeight = processedImage.getHeight();

        if (panelWidth>0 && panelHeight>0){
            Image scaled = bufferedImage.getScaledInstance(panelWidth, panelHeight, Image.SCALE_SMOOTH);
            labelPr.setIcon(new ImageIcon(scaled));
        }
    }
}
