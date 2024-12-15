import { LitElement, css, html } from "lit";

export class AirConditionerWdiget extends LitElement {
  // Define reactive properties
  static properties = {
    // internal states
    _active: { state: true },
  };

  constructor() {
    super();
    // set the default internal states
    this._active = false;
  }

  render() {
    return html`
      <div class="widget">
        <div class="widget-title">
          <span class="title-text"> Air Conditioner </span>
          <div>
            <toggle-button
              id="ac-toggle-btn"
              @toggled=${(e) => {
                this._active = e.detail.active;
              }}
            ></toggle-button>
          </div>
        </div>
        <div class="round-slider-container">
          <round-slider
            id="aircon-slider"
            min="15"
            max="30"
            value="20"
            step="0.1"
            valueLabel="Temperature"
            sliderWidth="10"
            ?disabled=${!this._active ? true : false}
          ></round-slider>
        </div>
        <div class="date-widget-container">
          <date-widget></date-widget>
        </div>
        <div class="input-slider-container">
          <input-slider
            id="humidity"
            value="0"
            unit="%"
            sliderWidth="130"
            sliderHeight="30"
            handleLength="30"
            ?disabled=${!this._active ? true : false}
          >
          </input-slider>
          <input-slider
            id="speed"
            value="0"
            sliderWidth="130"
            sliderHeight="30"
            handleLength="30"
            color1="#08783b"
            color2="#00bd56"
            color3="#f9fd50"
            ?disabled=${!this._active ? true : false}
          >
          </input-slider>
        </div>
      </div>
    `;
  }

  static styles = css`
    :host {
      display: block;
    }
    .widget {
      box-sizing: border-box;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      background-color: #686868;
      border-radius: 1rem;
      padding: 2.5rem;
      height: 100%;
    }
    .widget .widget-title {
      display: flex;
      justify-content: space-between;
      align-items: center;
    }
    .widget .widget-title .title-text {
      color: #ddd;
      font-size: 1.5rem;
    }
    .round-slider-container {
      display: flex;
      justify-content: center;
      margin: 1rem;
    }
    .date-widget-container {
      margin: 0 auto;
    }
    .input-slider-container {
      display: flex;
      justify-content: center;
      gap: 32px;
    }
    @media screen and (max-width: 1900px) {
      .widget {
        padding: 1rem;
      }
      .widget-title {
        font-size: 1rem;
      }
      .input-slider-container {
        justify-content: space-between;
        gap: 10px;
      }
    }
  `;
}

window.customElements.define("aircon-widget", AirConditionerWdiget);
