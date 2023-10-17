package Sliders;

import Frames.MainFrame;

import javax.swing.*;
import java.awt.*;

public class CMYK_Slider extends JPanel {
    private MainFrame frame;
    private JSlider cSlider;
    private JSlider mSlider;
    private JSlider ySlider;
    private JSlider kSlider;
    public CMYK_Slider(MainFrame mainFrame) {
        setLayout(new GridLayout(4,0));
        frame = mainFrame;
        cSlider = new JSlider(SwingConstants.HORIZONTAL, 0,100, frame.getCMYK().getC());
        mSlider = new JSlider(SwingConstants.HORIZONTAL, 0,100, frame.getCMYK().getM());
        mSlider.setValue(frame.getCMYK().getM());
        ySlider = new JSlider(SwingConstants.HORIZONTAL, 0,100, frame.getCMYK().getEY());
        kSlider = new JSlider(SwingConstants.HORIZONTAL, 0,100, frame.getCMYK().getK());

        add(cSlider);
        add(mSlider);
        add(ySlider);
        add(kSlider);

        cSlider.addChangeListener(e -> {
            if (cSlider.hasFocus()){
                frame.getCMYK().changeTextFields(cSlider.getValue(), frame.getCMYK().getM(),frame.getCMYK().getEY(),frame.getCMYK().getK());
                frame.getCMYK().makeChanges(frame.getCMYK().getEnterC());
            }
        });

        mSlider.addChangeListener(e -> {
            if (mSlider.hasFocus()){
                frame.getCMYK().changeTextFields(frame.getCMYK().getC(), mSlider.getValue(),frame.getCMYK().getEY(),frame.getCMYK().getK());
                frame.getCMYK().makeChanges(frame.getCMYK().getEnterM());
            }
        });
        ySlider.addChangeListener(e -> {
            if (ySlider.hasFocus()){
                frame.getCMYK().changeTextFields(frame.getCMYK().getC(),frame.getCMYK().getM(),ySlider.getValue(),frame.getCMYK().getK());
                frame.getCMYK().makeChanges(frame.getCMYK().getEnterY());
            }
        });
        kSlider.addChangeListener(e -> {
            if (kSlider.hasFocus()){
                frame.getCMYK().changeTextFields(frame.getCMYK().getC(), frame.getCMYK().getM(),frame.getCMYK().getEY(),kSlider.getValue());
                frame.getCMYK().makeChanges(frame.getCMYK().getEnterK());
            }
        });
    }

    public JSlider getcSlider() {
        return cSlider;
    }

    public JSlider getmSlider() {
        return mSlider;
    }

    public JSlider getySlider() {
        return ySlider;
    }

    public JSlider getkSlider() {
        return kSlider;
    }
}
