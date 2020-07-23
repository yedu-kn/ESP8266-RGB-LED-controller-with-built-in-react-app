import React from 'react';
import { IconButton } from '@material-ui/core';
import { FaLightbulb } from "react-icons/fa";
import { FaRegLightbulb } from "react-icons/fa";

const Bulb = ({color, powerChange, power }) => {
  return (
    <div className="tc pv5">
      <div className='' style={{display:'flex-inline', justifyContent:'center'}}>
        <IconButton aria-label="delete" onClick={powerChange}>
          {power ? ( <FaLightbulb size='7em' color={color} /> )
                 : ( <FaRegLightbulb size='7em' color={color} /> )
          }
        </IconButton>
      </div>
    </div>
  );
};

export default Bulb;
