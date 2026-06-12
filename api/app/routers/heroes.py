from fastapi import APIRouter, Depends
from sqlalchemy import text
from sqlalchemy.orm import Session
from api.app.database import get_db

router = APIRouter(
    prefix="/heroes"
)

@router.get("/")
def get_all_heroes(db: Session = Depends(get_db)):
    result = db.execute(
        text("SELECT * FROM heroes;")
    )

    tables = [row[0] for row in result]

    return {
        "database_found": True,
        "tables": tables
    }

