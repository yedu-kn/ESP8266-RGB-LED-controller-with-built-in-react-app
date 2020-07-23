import React from 'react';
import CircularSlider from '@fseehawer/react-circular-slider';

const Slider = ({ brightnessChange, color }) => {
  return (
    <div className="tc pb4">
      <CircularSlider
        label="Brightness"
        min={0}
        max={100}
        dataIndex={20}
        prependToValue=""
        appendToValue="%"
        labelColor="#fff"
        labelBottom={true}
        labelFontSize="20px"
        knobColor="#005a58"
        progressColorFrom='#fff'
        progressColorTo={color}
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
