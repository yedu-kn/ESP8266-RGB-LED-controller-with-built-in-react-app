import React from 'react';
import CircularSlider from '@fseehawer/react-circular-slider';

const Slider = ({ brightnessChange }) => {
  return (
    <div className="tc pt5">
      <CircularSlider
        label="Brightness"
        min={0}
        max={100}
        dataIndex={20}
        prependToValue=""
        appendToValue="%"
        labelColor="#005a58"
        labelBottom={true}
        labelFontSize="20px"
        knobColor="#005a58"
        progressColorFrom="#00bfbd"
        progressColorTo="#005a58"
        progressSize={20}
        trackColor="#eeeeee"
        trackSize={24}
        knobeDraggable={false}
        onChange={brightnessChange}
      ></CircularSlider>
    </div>
  );
};

export default Slider;
