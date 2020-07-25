import React, { Component } from 'react';
import Slider from './Slider';
import ColorPicker1 from './ColorPicker1';
import ColorPicker2 from './ColorPicker2';
import Carousel from 'nuka-carousel';
import './App.css';
import { IoIosArrowDropleftCircle, IoIosArrowDroprightCircle } from "react-icons/io";
import Effects from './Effects';
import Bulb from './Bulb';
import {debounce} from 'lodash';

class App extends Component {
  state = {
    power:true,
    effect: 1,
    speed:30,
    Brightness: 20,
    R: 156,
    G: 39,
    B: 176,
    color: '#9C27B0',
    speedDisable:true
  };

  onBrightnessChange = (event) => {
    this.setState(({ Brightness: event }),
    ()=> this.postData());
  };

  onColorChange = (color) => {
    this.setState(({
      R: color.rgb.r,
      G: color.rgb.g,
      B: color.rgb.b,
      color: color.hex,
    }),
    () => this.postData());
  };

  onEffectChange = (effectvalue) => {
    this.setState(({effect: effectvalue}),
    () => this.postData());
    // eslint-disable-next-line
    if (effectvalue == 1){
      this.setState({speedDisable: true});
    } else {this.setState({speedDisable: false})}
    
  }

  onSpeedChange = (event, speedValue) => {
    this.setState(({speed: speedValue}),
    () => this.postData());
  }

  onPowerChange = () => {
    this.setState(({power: !this.state.power}),
      () => this.postData());
  }

  postData = debounce(() => {
    const formdata = new FormData();
    Object.keys(this.state).forEach(k => {
      formdata.append(k, this.state[k])
    })

    var requestOptions = {
      method: 'POST',
      body: formdata,
      redirect: 'follow',
    };

    // fetch('http://192.168.1.12/postform/', requestOptions) // replace with esp ip
    fetch('/postform/', requestOptions) // on hw ip is not needed
      .then((response) => response.text())
      //.then((result) => console.log(result))
      .catch((error) => console.log('error', error));
  }, 300);

  render() {
    return (
      <div>
        <div> 
          <div>
            <Bulb               
              color={this.state.color}
              powerChange={this.onPowerChange}
              power={this.state.power} />
          </div>
          <div style={{display: 'flex', justifyContent: 'center'}}>
            <Carousel
              className={'slide'}
              dragging={false}
              swiping={false}
              wrapAround={true}
              width={'400px'}
              heightMode={'max'}
              defaultControlsConfig={{
                nextButtonText: <IoIosArrowDroprightCircle size='1.6em' />,
                prevButtonText: <IoIosArrowDropleftCircle size='1.6em'/>,
                nextButtonStyle: {background:'none', outline:'none'},
                prevButtonStyle: {background:'none', outline:'none'},
                pagingDotsStyle: {fill: 'yellow', outline:'none'}
              }}
              >
              <Slider brightnessChange={this.onBrightnessChange} color={this.state.color} />
              <ColorPicker1 colorChange={this.onColorChange} color={this.state.color} />
              <ColorPicker2 colorChange={this.onColorChange} color={this.state.color} />
              <Effects
                effectChange={this.onEffectChange}
                speedChange={this.onSpeedChange}
                speed={this.state.speed}
                speedDisable={this.state.speedDisable}
              />
            </Carousel>
          </div>
        </div>
      </div>
    );
  }
}

export default App;
