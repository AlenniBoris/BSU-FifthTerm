package Sliders;

import Frames.MainFrame;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;

public class RGB_Slider extends JPanel {
    private MainFrame frame;
    private JSlider rSlider;
    private JSlider gSlider;
    private JSlider bSlider;
    public RGB_Slider(MainFrame mainFrame) {
        setLayout(new GridLayout(3,0));
        frame = mainFrame;
        rSlider = new JSlider(SwingConstants.HORIZONTAL, 0,255, frame.getColorPanel().getBackground().getRed());
        gSlider = new JSlider(SwingConstants.HORIZONTAL, 0,255, frame.getColorPanel().getBackground().getGreen());
        bSlider = new JSlider(SwingConstants.HORIZONTAL, 0,255, frame.getColorPanel().getBackground().getBlue());

        add(rSlider);
        add(gSlider);
        add(bSlider);
        rSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if (rSlider.hasFocus()){
                    frame.getRGB().changeTextFields(rSlider.getValue(), frame.getColorPanel().getBackground().getGreen(), frame.getColorPanel().getBackground().getBlue());
                    frame.getRGB().makeChanges(frame.getRGB().getEnterR());
                }
            }
        });

        gSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if (gSlider.hasFocus()){
                    frame.getRGB().changeTextFields(frame.getColorPanel().getBackground().getRed(), gSlider.getValue(), frame.getColorPanel().getBackground().getBlue());
                    frame.getRGB().makeChanges(frame.getRGB().getEnterG());
                }
            }
        });
        bSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if (bSlider.hasFocus()){
                    frame.getRGB().changeTextFields(frame.getColorPanel().getBackground().getRed(), frame.getColorPanel().getBackground().getGreen(), bSlider.getValue());
                    frame.getRGB().makeChanges(frame.getRGB().getEnterB());
                }
            }
        });
    }

    public JSlider getrSlider() {
        return rSlider;
    }

    public JSlider getgSlider() {
        return gSlider;
    }

    public JSlider getbSlider() {
        return bSlider;
    }
}

