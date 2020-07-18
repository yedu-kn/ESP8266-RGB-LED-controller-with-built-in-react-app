import React, { Component } from 'react';
import Slider from './Slider';
import ColorPicker from './ColorPicker';
import './App.css';

class App extends Component {
  state = {
    Brightness: 20,
    R: 156,
    G: 39,
    B: 176,
    color: '#9C27B0',
  };

  onBrightnessChange = (event) => {
    this.setState({ Brightness: event });
  };

  onColorChange = (color) => {
    this.setState({
      R: color.rgb.r,
      G: color.rgb.g,
      B: color.rgb.b,
      color: color.hex,
    });
  };

  render() {
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/server', true);

    //Send the proper header information along with the request
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');

    xhr.onreadystatechange = function () {
      // Call a function when the state changes.
      if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
        // Request finished. Do processing here.
      }
    };
    xhr.send(
      `Brightness=${this.state.Brightness}&R=${this.state.R}&G=${this.state.G}&B=${this.state.B}`
    );
    //xhr.send("value2=34");
    // xhr.send(document);

    return (
      <div style={{ display: 'flex-inline', justifyContent: 'center' }}>
        <div>
          <Slider brightnessChange={this.onBrightnessChange} />
          <ColorPicker
            colorChange={this.onColorChange}
            color={this.state.color}
          />
        </div>
      </div>
    );
  }
}

export default App;
