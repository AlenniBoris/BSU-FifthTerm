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
        setLayout(new GridLayout(0, 2));

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
        processedImage = new JPanel(new GridLayout(1, 2, 0, 4));
        labelPr = new JLabel();
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
        labelOr.setIcon(new ImageIcon(bufferedImage));
        originalImage.add(labelOr);
    }

    public void setPicProcessed(BufferedImage bufferedImage) {
        labelPr.setIcon(new ImageIcon(bufferedImage));
        processedImage.add(labelPr);
    }

    public void setPicNiblack(BufferedImage bufferedImage) {
        labelPr1.setIcon(new ImageIcon(bufferedImage));
        processedImage.add(labelPr1);
    }

    public JLabel getLabelPr1() {
        return labelPr1;
    }
}
