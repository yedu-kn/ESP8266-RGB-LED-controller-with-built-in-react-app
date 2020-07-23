import React from 'react';
import { SketchPicker } from 'react-color';

class ColorPicker1 extends React.Component {
  render() {
    const { colorChange, color } = this.props;

    return (
      <div
        style={{ display: 'flex', justifyContent: 'center', outline: '0px solid transparent' }}
      >
        <SketchPicker
          style={{ outline: 'none' }}
          disableAlpha={true}
          width={260}
          color={color}
          onChange={colorChange}
          presetColors={[]}
        />
      </div>
    );
  }
}

export default ColorPicker1;
