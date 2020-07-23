import React from 'react';
import { SwatchesPicker } from 'react-color';

class ColorPicker2 extends React.Component {
  render() {
    const { colorChange, color } = this.props;

    return (
      <div
        style={{ display: 'flex', justifyContent: 'center' }}
      >
        <SwatchesPicker
          disableAlpha={true}
          width={275}
          height={265}
          color={color}
          onChange={colorChange}
          presetColors={[]}
        />
      </div>
    );
  }
}

export default ColorPicker2;
