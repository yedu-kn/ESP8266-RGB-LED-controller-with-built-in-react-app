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
    const formdata = new FormData();
    Object.keys(this.state).forEach(k => {
      formdata.append(k, this.state[k])
    })

    var requestOptions = {
      method: 'POST',
      body: formdata,
      redirect: 'follow',
    };

    fetch('http://192.168.1.12/postform/', requestOptions)
      .then((response) => response.text())
      .then((result) => console.log(result))
      .catch((error) => console.log('error', error));
  }

  render() {
    return (
      <div style={{ display: 'flex-inline', justifyContent: 'center' }}>
        <div>
          <Slider
            brightnessChange={this.onBrightnessChange}
            color={this.state.color}
          />
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
