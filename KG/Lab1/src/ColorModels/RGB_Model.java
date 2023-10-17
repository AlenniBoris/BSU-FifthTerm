package ColorModels;

import Frames.MainFrame;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import java.awt.*;

public class RGB_Model extends JPanel {
    private JTextField enterR;
    private JTextField enterG;
    private JTextField enterB;

    private MainFrame frame;

    public RGB_Model(MainFrame mainFrame) {
        this.enterR = new JTextField("0");
        this.enterG = new JTextField("0");
        this.enterB = new JTextField("0");
        this.frame = mainFrame;

        setLayout(new GridLayout(4,0));
        add(new JLabel("RGB"));
        add(enterR);
        addListener(enterR);
        add(enterG);
        addListener(enterG);
        add(enterB);
        addListener(enterB);

    }

    public JTextField getEnterR() {
        return enterR;
    }

    public JTextField getEnterG() {
        return enterG;
    }

    public JTextField getEnterB() {
        return enterB;
    }

    public int getR() {
        return Integer.parseInt(enterR.getText());
    }

    public int getG() {
        return Integer.parseInt(enterG.getText());
    }

    public int getB() {
        return Integer.parseInt(enterB.getText());
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
                int value = Integer.parseInt(textField.getText());
                if (value >= 0 && value <= 255){
                    if (textField == enterR){
                        int G = Integer.parseInt(enterG.getText());
                        int B = Integer.parseInt(enterB.getText());
                        frame.getColorPanel().setBackground(new Color(value, G, B));
                        changeCMYK(value,G,B);
                        changeHSL(value,G,B);
                        frame.getSliderPanel().getRgbSlider().getrSlider().setValue(value);
                    } else if (textField == enterG) {
                        int R = Integer.parseInt(enterR.getText());
                        int B = Integer.parseInt(enterB.getText());
                        frame.getColorPanel().setBackground(new Color(R, value, B));
                        changeHSL(R,value,B);
                        frame.getSliderPanel().getRgbSlider().getgSlider().setValue(value);
                    } else {
                        int R = Integer.parseInt(enterR.getText());
                        int G = Integer.parseInt(enterG.getText());
                        frame.getColorPanel().setBackground(new Color(R, G, value));
                        changeHSL(R,G,value);
                        frame.getSliderPanel().getRgbSlider().getbSlider().setValue(value);
                    }
                }else {
                    JOptionPane.showMessageDialog(frame,"Enter number in 0..255");
                }
            }catch (NumberFormatException e){
                JOptionPane.showMessageDialog(frame,"Enter only digits");
            }
        }
    }
    public void changeTextFields(int R, int G, int B){
        enterR.setText(Integer.toString(R));
        enterG.setText(Integer.toString(G));
        enterB.setText(Integer.toString(B));

        frame.getSliderPanel().getRgbSlider().getrSlider().setValue(R);
        frame.getSliderPanel().getRgbSlider().getgSlider().setValue(G);
        frame.getSliderPanel().getRgbSlider().getbSlider().setValue(B);
    }

    public void changeCMYK(int R, int G, int B){
        double percentageR = R / 255.0 * 100;
        double percentageG = G / 255.0 * 100;
        double percentageB = B / 255.0 * 100;

        double K = 100 - Math.max(Math.max(percentageR, percentageG), percentageB);

        if (K == 100) {
            frame.getCMYK().changeTextFields(0,0,0,100);
            return;
        }

        int C = (int)((100 - percentageR - K) / (100 - K) * 100);
        int M = (int)((100 - percentageG - K) / (100 - K) * 100);
        int Y = (int)((100 - percentageB - K) / (100 - K) * 100);

        frame.getCMYK().changeTextFields(C,M,Y,(int) K);
    }

    public void changeHSL(int R, int G, int B){
        double r = R / 255.0;
        double g = G / 255.0;
        double b = B / 255.0;

        double max = Math.max(r, Math.max(g, b));
        double min = Math.min(r, Math.min(g, b));

        double h, s, l;
        h = 0;
        s = 0;
        l = (max + min) / 2.0;
        double delta = (max-min);

        if (max == min) {
            s = 0;
        } else {
            s = delta / (1-Math.abs(2*l-1));
        }

        if(delta == 0){
            h = 0f;
        } else if (max == r) {
            h = 60*(((g-b)/delta)%6);
        } else if (max == g) {
            h = 60*(((b-r)/delta)+2);
        } else if (max == b) {
            h = 60*(((b-r)/delta)+4);
        }

        frame.getHSL().changeTextFields((int) h, (double)(s*100), (double)(l*100));
    }

}
