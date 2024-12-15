import { LitElement, css, html } from "lit";
import Chart from "chart.js/auto";
import { tempData } from "./data";
import zoomPlugin from "chartjs-plugin-zoom";
import { DateTime } from "luxon";

export class TemperatureChart extends LitElement {
  constructor() {
    super();
    // register ChartJS plugin
    Chart.register(zoomPlugin);
  }

  // query the canvas element in the internal DOM using getter pattern
  get _canvas() {
    return this.renderRoot.querySelector("canvas");
  }

  // Invoked when the custom element is initially rendered
  firstUpdated() {
    this.tempChart(tempData);
  }

  /**
   * Initialize ChartJS
   * @param {Object} data Last year data
   * @returns {Object} ChartJS object
   */
  tempChart(data) {
    return new Chart(this._canvas, {
      type: "line",
      data: {
        labels: data.map((d) =>
          DateTime.now().minus({ days: d.date }).toFormat("dd LLL")
        ),
        datasets: [
          {
            label: "Temperature",
            data: data.map((d) => d.value),
            borderWidth: 1,
            borderColor: "#ff6384",
            backgroundColor: "#ffb1c1",
            fill: "start",
          },
        ],
      },
      options: {
        maintainAspectRatio: false,
        scales: {
          y: {
            min: 15,
            max: 30,
            display: false,
            ticks: {
              display: false,
            },
          },
          x: {
            grid: {
              tickLength: 10,
              drawOnChartArea: false,
            },
          },
        },
        elements: {
          line: {
            tension: 0.4,
          },
        },
        plugins: {
          zoom: {
            zoom: {
              wheel: {
                enabled: true,
              },
              pinch: {
                enabled: true,
              },
              mode: "x",
              scaleMode: "x",
            },
            pan: {
              enabled: true,
              mode: "x",
              scaleMode: "x",
            },
            limits: {
              x: { min: 1, max: 30, minRange: 2 },
            },
          },
        },
      },
    });
  }

  render() {
    return html` <div class="container"><canvas id="myChart"></canvas></div> `;
  }

  static styles = css`
    :host {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100%;
    }
    .container {
      position: relative;
      width: 95%;
      height: 70vh;
    }
  `;
}

window.customElements.define("temperature-chart", TemperatureChart);
