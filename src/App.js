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
    this.postData();
  };

  onColorChange = (color) => {
    this.setState({
      R: color.rgb.r,
      G: color.rgb.g,
      B: color.rgb.b,
      color: color.hex,
    });
    this.postData();
  };

  postData() {
    // TODO: send to server after debounce
    console.log(this.state);
    fetch('https://esp.local', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(this.state),
    })
    .then(response => response.json())
    .then(data => {
      console.log('Success:', data);
    })
  }

  render() {
    return (
      <div style={{ display: 'flex-inline', justifyContent: 'center' }}>
        <div>
          <Slider brightnessChange={this.onBrightnessChange}  color={this.state.color}/>
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
