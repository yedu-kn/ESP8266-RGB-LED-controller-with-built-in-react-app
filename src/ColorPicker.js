import React from 'react';
import { SketchPicker } from 'react-color';

class ColorPicker extends React.Component {
  render() {
    const { colorChange, color } = this.props;

    return (
      <div
        className="pt5"
        style={{ display: 'flex', justifyContent: 'center' }}
      >
        <SketchPicker
          disableAlpha={true}
          width={250}
          color={color}
          onChange={colorChange}
          presetColors={[]}
        />
      </div>
    );
  }
}

export default ColorPicker;
