import { LitElement, css, html } from "lit";
import Chart from "chart.js/auto";
import { powerData1 } from "./data-1";
import { powerData2 } from "./data-2";

export class GraphWidget extends LitElement {
  constructor() {
    super();
  }

  // query the canvas element in the internal DOM using getter pattern
  get _canvas() {
    return this.renderRoot.querySelector("canvas");
  }

  // Invoked when the custom element is initially rendered
  firstUpdated() {
    this.powerChart(powerData1, powerData2);
  }

  /**
   * Initialize ChartJS
   * @param {Object} data1 Last year data
   * @param {Object} data2 Current year data
   * @returns {Object} ChartJS object
   */
  powerChart(data1, data2) {
    return new Chart(this._canvas, {
      type: "line",
      data: {
        labels: data2.map((d) => d.month),
        datasets: [
          {
            label: "This Year",
            data: data2.map((d) => d.value),
            borderWidth: 3,
            fill: "origin",
            type: "line",
            pointBackgroundColor: "white",
          },
          {
            label: "Last Year",
            data: data1.map((d) => d.value),
            borderWidth: 3,
            fill: "origin",
            pointBackgroundColor: "white",
          },
        ],
      },
      options: {
        maintainAspectRatio: false,
        scales: {
          y: {
            min: 500,
            max: 1000,
            display: true,
            title: {
              display: true,
              text: "Power Consumption(kWh)",
            },
            ticks: {
              display: true,
            },
          },
          x: {
            grid: {
              tickLength: 11,
              drawOnChartArea: true,
            },
          },
        },
        elements: {
          line: {
            tension: 0.4,
          },
        },
      },
    });
  }

  render() {
    return html`
      <div class="container">
        <canvas id="myChart"></canvas>
      </div>
    `;
  }

  static styles = css`
    :host {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100%;
      width: 100%;
    }
    .container {
      width: 100%;
      height: 100%;
    }
  `;
}

window.customElements.define("graph-widget", GraphWidget);
