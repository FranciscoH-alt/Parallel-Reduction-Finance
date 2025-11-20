import React, { useState } from "react";

type ReductionResult = {
  count: number;
  sum: number;
  average: number;
  min: number;
  max: number;
  gpuMilliseconds: number;
  cpuMilliseconds: number;
};

const API_URL =
  (import.meta as any).env.VITE_API_URL ?? "http://localhost:5000";

const App: React.FC = () => {
  const [valuesText, setValuesText] = useState("100, 105.5, 98.2, 110");
  const [result, setResult] = useState<ReductionResult | null>(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const handleRun = async () => {
    setError(null);
    setResult(null);

    // Parse numbers from text area
    const rawPieces = valuesText
      .split(/[\s,]+/)
      .map((v) => v.trim())
      .filter((v) => v.length > 0);

    const numbers = rawPieces
      .map((v) => Number(v))
      .filter((v) => !Number.isNaN(v));

    if (numbers.length === 0) {
      setError("Please enter at least one valid number.");
      return;
    }

    setLoading(true);

    try {
      const response = await fetch(`${API_URL}/api/reduce`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ values: numbers }),
      });

      if (!response.ok) {
        throw new Error(`Backend returned ${response.status}`);
      }

      const data: ReductionResult = await response.json();
      setResult(data);
    } catch (err: any) {
      console.error(err);
      setError(
        "Could not reach the CUDA backend. Make sure it is running on your buddy's PC (or on localhost)."
      );
    } finally {
      setLoading(false);
    }
  };

  const handleFillDemo = () => {
    setValuesText("10500, 10620, 10430, 10780, 10950, 10890, 11020");
  };

  return (
    <div className="app">
      <header className="app-header">
        <h1>Parallel Reduction Finance</h1>
        <p className="subtitle">
          GPU-accelerated aggregation of portfolio values (CUDA on your buddy&apos;s PC, UI on your Mac).
        </p>
      </header>

      <main className="main-grid">
        <section className="card">
          <h2>Input Portfolio Data</h2>
          <p className="help-text">
            Paste a list of daily portfolio values or returns (comma or space
            separated).
          </p>

          <textarea
            className="textarea"
            value={valuesText}
            onChange={(e) => setValuesText(e.target.value)}
            rows={7}
          />

          <div className="button-row">
            <button className="btn secondary" type="button" onClick={handleFillDemo}>
              Use demo data
            </button>
            <button
              className="btn primary"
              type="button"
              onClick={handleRun}
              disabled={loading}
            >
              {loading ? "Running CUDA reduction..." : "Run Parallel Reduction"}
            </button>
          </div>

          <p className="api-note">
            API URL:&nbsp;
            <code>{API_URL}/api/reduce</code>
          </p>
        </section>

        <section className="card">
          <h2>Results</h2>

          {error && <div className="alert error">{error}</div>}

          {!error && !result && !loading && (
            <p className="placeholder">
              Run the reduction to see GPU vs CPU timing and aggregated
              portfolio stats.
            </p>
          )}

          {loading && (
            <p className="placeholder">
              Launching GPU kernel / CPU baseline&hellip;
            </p>
          )}

          {result && !error && (
            <>
              <div className="stats-grid">
                <div className="stat">
                  <span className="label">Observations</span>
                  <span className="value">{result.count}</span>
                </div>
                <div className="stat">
                  <span className="label">Total (Sum)</span>
                  <span className="value">
                    {result.sum.toLocaleString(undefined, {
                      maximumFractionDigits: 2,
                    })}
                  </span>
                </div>
                <div className="stat">
                  <span className="label">Average</span>
                  <span className="value">
                    {result.average.toLocaleString(undefined, {
                      maximumFractionDigits: 2,
                    })}
                  </span>
                </div>
                <div className="stat">
                  <span className="label">Min</span>
                  <span className="value">
                    {result.min.toLocaleString(undefined, {
                      maximumFractionDigits: 2,
                    })}
                  </span>
                </div>
                <div className="stat">
                  <span className="label">Max</span>
                  <span className="value">
                    {result.max.toLocaleString(undefined, {
                      maximumFractionDigits: 2,
                    })}
                  </span>
                </div>
              </div>

              <h3>Performance (ms)</h3>
              <div className="timing-row">
                <div className="timing-chip gpu">
                  <span className="timing-label">GPU</span>
                  <span className="timing-value">
                    {result.gpuMilliseconds.toFixed(3)} ms
                  </span>
                </div>
                <div className="timing-chip cpu">
                  <span className="timing-label">CPU</span>
                  <span className="timing-value">
                    {result.cpuMilliseconds.toFixed(3)} ms
                  </span>
                </div>
              </div>

              <p className="note">
                On your Mac, these numbers only appear once the CUDA backend is
                running on a reachable machine (e.g., your buddy&apos;s PC).
              </p>
            </>
          )}
        </section>
      </main>

      <footer className="footer">
        <span>Parallel-Reduction-Finance · GPU demo UI</span>
      </footer>
    </div>
  );
};

export default App;
