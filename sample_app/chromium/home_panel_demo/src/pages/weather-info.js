import { LitElement, html } from "lit";

/**
 * Class to create Weather Info page element
 */
export class WeatherInfoPage extends LitElement {
  constructor() {
    super();
  }

  render() {
    return html` <temperature-chart></temperature-chart> `;
  }
}

window.customElements.define("wheather-info-page", WeatherInfoPage);
