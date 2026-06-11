from sqlalchemy import text
from fastapi import Depends, FastAPI
from sqlalchemy.orm import Session
from api.app.database import get_db

app = FastAPI(
    title="The Lost Force",
    description="Front-end representation of the backend side",
    version="1.0"
)

@app.get("/test-db")
def test_db(db: Session = Depends(get_db)):
    result = db.execute(
        text("SELECT * FROM heroes;")
    )

    tables = [row[0] for row in result]

    return {
        "database_found": True,
        "tables": tables
    }