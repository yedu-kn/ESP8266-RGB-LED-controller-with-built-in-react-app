import React from 'react';
import { RadioGroup, RadioButton } from 'react-radio-buttons';

import Typography from '@material-ui/core/Typography';
import Slider from '@material-ui/core/Slider';


const Effects = ({ effectChange, speedChange, speed, speedDisable }) => {
  
  return (
    <div className='ph5'>
      <RadioGroup value='0' onChange={ effectChange }>
        <RadioButton value="1" iconSize={20}>
          No-effects
        </RadioButton>
        <RadioButton value="2" iconSize={20}>
          Fade
        </RadioButton>
        <RadioButton value="3" iconSize={20}>
          Colour Change
        </RadioButton>
        </RadioGroup>

        <div>
          <Typography id="continuous-slider" gutterBottom>
            Speed
          </Typography>
          <Slider disabled={speedDisable} value={speed} onChange={speedChange} aria-labelledby="continuous-slider" />
        </div>        
    </div>
  );
};

export default Effects;