package Sliders;

import Frames.MainFrame;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;


public class HSL_Slider extends JPanel {
    private MainFrame frame;
    private JSlider hSlider;
    private JSlider sSlider;
    private JSlider lSlider;
    public HSL_Slider(MainFrame mainFrame) {
        setLayout(new GridLayout(3,0));
        frame = mainFrame;
        hSlider = new JSlider(SwingConstants.HORIZONTAL, 0,100, frame.getHSL().getH());
        sSlider = new JSlider(SwingConstants.HORIZONTAL, 0,100, (int) frame.getHSL().getS());
        lSlider = new JSlider(SwingConstants.HORIZONTAL, 0,100, (int) frame.getHSL().getL());

        add(hSlider);
        add(sSlider);
        add(lSlider);
        hSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if (hSlider.hasFocus()){
                    frame.getHSL().changeTextFields(hSlider.getValue(), frame.getHSL().getS(), frame.getHSL().getL());
                    frame.getHSL().makeChanges(frame.getHSL().getEnterH());
                }
            }
        });

        sSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if (sSlider.hasFocus()){
                    frame.getHSL().changeTextFields(frame.getHSL().getH(), sSlider.getValue(), frame.getHSL().getL());
                    frame.getHSL().makeChanges(frame.getHSL().getEnterS());
                }
            }
        });
        lSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if (lSlider.hasFocus()){
                    frame.getHSL().changeTextFields(frame.getHSL().getH(), frame.getHSL().getS(), lSlider.getValue());
                    frame.getHSL().makeChanges(frame.getHSL().getEnterL());
                }
            }
        });
    }

    public JSlider gethSlider() {
        return hSlider;
    }

    public JSlider getsSlider() {
        return sSlider;
    }

    public JSlider getlSlider() {
        return lSlider;
    }
}
