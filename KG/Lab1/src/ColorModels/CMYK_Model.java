package ColorModels;

import Frames.MainFrame;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import java.awt.*;

public class CMYK_Model extends JPanel{
    private JTextField enterC;
    private JTextField enterM;
    private JTextField enterY;
    private JTextField enterK;

    private MainFrame frame;

    public CMYK_Model(MainFrame mainFrame) {
        this.enterC = new JTextField("0");
        this.enterM = new JTextField("0");
        this.enterY = new JTextField("0");
        this.enterK = new JTextField("0");
        this.frame = mainFrame;

        setLayout(new GridLayout(5,0));
        add(new JLabel("CMYK(%)"));
        add(enterC);
        addListener(enterC);
        add(enterM);
        addListener(enterM);
        add(enterY);
        addListener(enterY);
        add(enterK);
        addListener(enterK);
    }

    public JTextField getEnterC() {
        return enterC;
    }

    public JTextField getEnterM() {
        return enterM;
    }

    public JTextField getEnterY() {
        return enterY;
    }

    public JTextField getEnterK() {
        return enterK;
    }

    public int getC() {
        return Integer.parseInt(enterC.getText());
    }
    public int getM() {
        return Integer.parseInt(enterM.getText());
    }
    public int getEY() {
        return Integer.parseInt(enterY.getText());
    }
    public int getK() {
        return Integer.parseInt(enterK.getText());
    }


    private void addListener(JTextField textField){
        textField.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                if (textField.hasFocus()){
                    makeChanges(textField);
                }
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                if (textField.hasFocus()){
                    makeChanges(textField);
                }
            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                if (textField.hasFocus()){
                    makeChanges(textField);
                }
            }
        });
    }

    public void makeChanges(JTextField textField){
        if (!textField.getText().isEmpty()){
            try{
                double value = Integer.parseInt(textField.getText())*Math.pow(10,-2);
                if (value >= 0 && value <= 1){
                    if (textField == enterC){
                        changeColor(value, "C");
                    } else if (textField == enterM) {
                        changeColor(value, "M");
                    } else if (textField == enterY){
                        changeColor(value, "Y");
                    } else {
                        changeColor(value, "K");
                    }
                }else {
                    JOptionPane.showMessageDialog(frame,"Enter number in 0..100");
                }
            }catch (NumberFormatException e){
                JOptionPane.showMessageDialog(frame,"Enter only digits");
            }
        }
    }

    private void changeColor(double value, String color){
        switch(color){
            case "C" ->{
                double M = Integer.parseInt(enterM.getText()) * Math.pow(10,-2);
                double Y = Integer.parseInt(enterY.getText()) * Math.pow(10,-2);
                double K = Integer.parseInt(enterK.getText()) * Math.pow(10,-2);

                double r = 255 * (1 - value) * (1 - K);
                double g = 255 * (1 - M) * (1 - K);
                double b = 255 * (1 - Y) * (1 - K);

                frame.getColorPanel().setBackground(new Color((int) r, (int) g, (int) b));
                changeRGB((int) r, (int) g, (int) b);
                frame.getRGB().changeHSL((int) r, (int) g, (int) b);
                frame.getSliderPanel().getCmykSlider().getcSlider().setValue((int) Math.round(value*100));
            }
            case "M" ->{
                double C = Integer.parseInt(enterC.getText()) * Math.pow(10,-2);
                double Y = Integer.parseInt(enterY.getText()) * Math.pow(10,-2);
                double K = Integer.parseInt(enterK.getText()) * Math.pow(10,-2);

                double r = 255 * (1 - C) * (1 - K);
                double g = 255 * (1 - value) * (1 - K);
                double b = 255 * (1 - Y/100) * (1 - K/100);

                frame.getColorPanel().setBackground(new Color((int) r, (int) g, (int) b));
                changeRGB((int) r, (int) g, (int) b);
                frame.getRGB().changeHSL((int) r, (int) g, (int) b);
                frame.getSliderPanel().getCmykSlider().getmSlider().setValue((int) Math.round(value*100));
            }
            case "Y" ->{
                double C = Integer.parseInt(enterC.getText()) * Math.pow(10,-2);
                double M = Integer.parseInt(enterM.getText()) * Math.pow(10,-2);
                double K = Integer.parseInt(enterK.getText()) * Math.pow(10,-2);

                double r = 255 * (1 - C) * (1 - K);
                double g = 255 * (1 - M) * (1 - K);
                double b = 255 * (1 - value) * (1 - K);

                frame.getColorPanel().setBackground(new Color((int) r, (int) g, (int) b));
                changeRGB((int) r, (int) g, (int) b);
                frame.getRGB().changeHSL((int) r, (int) g, (int) b);
                frame.getSliderPanel().getCmykSlider().getySlider().setValue((int) Math.round(value*100));
            }
            default -> {
                double C = Integer.parseInt(enterC.getText()) * Math.pow(10,-2);
                double M = Integer.parseInt(enterM.getText()) * Math.pow(10,-2);
                double Y = Integer.parseInt(enterY.getText()) * Math.pow(10,-2);

                double r = (int) (255 * (1 - C) * (1 - value));
                double g = (int) (255 * (1 - M) * (1 - value));
                double b = (int) (255 * (1 - Y) * (1 - value));

                frame.getColorPanel().setBackground(new Color((int) r, (int) g, (int) b));
                changeRGB((int) r, (int) g, (int) b);
                frame.getRGB().changeHSL((int) r, (int) g, (int) b);
                frame.getSliderPanel().getCmykSlider().getkSlider().setValue((int) Math.round(value*100));
            }
        }
    }

    public void changeTextFields(int C, int M, int Y, int K){
        enterC.setText(Integer.toString(C));
        enterM.setText(Integer.toString(M));
        enterY.setText(Integer.toString(Y));
        enterK.setText(Integer.toString(K));

        frame.getSliderPanel().getCmykSlider().getcSlider().setValue(C);
        frame.getSliderPanel().getCmykSlider().getmSlider().setValue(M);
        frame.getSliderPanel().getCmykSlider().getySlider().setValue(Y);
        frame.getSliderPanel().getCmykSlider().getkSlider().setValue(K);
    }

    private void changeRGB(int R, int G, int B){
        frame.getRGB().changeTextFields(R,G,B);
    }
}
